/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#include "Internal.h"

namespace Internal
{
	unsigned int SavedResultCounter = 0;
	vector<SavedResult> SavedResults;

	string ErrorMessage(string message)
	{
		return (string(RETURN_ERROR) + string(PARAM_DELIMETER) + string(message));
	};

	void TruncateString(string &s, const int &size)
	{
		if (s.size() > (unsigned int) size)
		{
			int chunks = CountTruncChunks(s, size);
			SavedResult newResult = { SavedResultCounter, size, chunks, s };
			SavedResults.push_back(newResult);
			s = string(RETURN_TRUNCATED) + string(PARAM_DELIMETER) + to_string(SavedResultCounter) + string(PARAM_DELIMETER) + to_string(chunks);
			++SavedResultCounter;
		};
	};

	int CountTruncChunks(const string &s, const int &size)
	{
		return ((int) ceil(s.size() / size));
	};

	string GetTruncChunks(int resultHandle, int chunk)
	{
		vector<SavedResult>::iterator savedRes = SavedResults.begin();
		string returnString = RETURN_NULL;
		while (savedRes != SavedResults.end()) {
			if (savedRes->handle == resultHandle) {
				int lower = savedRes->chunkSize * (chunk - 1);
				int upper = min<int>((savedRes->chunkSize * chunk), (savedRes->result).length());
				returnString = (savedRes->result).substr(lower, (upper - lower));
				if (chunk == savedRes->chunks) // Last Chunk
					SavedResults.erase(savedRes);
				break;
			};
			++savedRes;
		};
		return returnString;
	};

	namespace Strings
	{
		char* GetNonConstStr(const string &s)
		{
			static std::vector<char> var;
			var.assign(s.begin(),s.end());
			var.push_back('\0');
			return &var[0];
		};

		vector<string> SplitString(const string &s, const string &delim, int maxi)
		{
			vector<string> elements;
			size_t lastPos = 0;
			int i = 0;
			do {
				size_t end;
				size_t pos = s.find(delim, lastPos);
				if ((pos == string::npos) || ((i >= maxi) && (maxi != -1))) {
					end = s.length();
				} else {
					end = pos;
					pos += delim.length();
				};
				elements.push_back(s.substr( lastPos, (end - lastPos) ));
				lastPos = pos;
				++i;
			} while ((lastPos != string::npos) && ((i <= maxi) || (maxi == -1)));
			return elements;
		};

		string BoolToString(const bool &value)
		{
			if (value)
				return "true";
			else
				return "false";
		};

		string VectorToSQF(const vector<string> &v)
		{
			string result = "[";
			for (vector<string>::const_iterator n = v.begin(); n != v.end(); ++n)
			{
				if (n != v.begin())
					result += ",";
				result += string("\"") + *n + string("\"");
			};
			result += "]";
			return result;
		};

		string SMatchToSQF(const smatch &m)
		{
			string result = "[";
			int i = 0;
			for (auto x:m)
			{
				if (i != 0)
					result += ",";
				result += string("\"") + x.str() + string("\"");
				++i;
			}
			result += "]";
			return result;
		};
	};

	namespace Threading
	{
		// Variables
		bool runMain = true;
		unsigned int threadCounter = 0;
		WorkerThread *threadAtt = nullptr;
		vector<WorkerThread*> finishedThreads;
		mutex mainCom;
		mutex sendCom;
		condition_variable cv;

		WorkerThread* RetrieveFinishedThread(unsigned int threadHandle, bool removeThread)
		{
			vector<WorkerThread*>::const_iterator i = finishedThreads.begin();
			WorkerThread *result = nullptr;
			while ((i != finishedThreads.end()) && (result == nullptr))
			{
				if ((*i)->handle == threadHandle) {
					result = *i;
					if (removeThread)
						finishedThreads.erase(i);
				};
				++i;
			};
			return result;
		};

		WorkerThread* GetOldestWorker( vector<WorkerThread*> &wThreads )
		{
			chrono::steady_clock::time_point oldestTime = chrono::system_clock::now();;
			WorkerThread* wThread = nullptr;
			if (wThreads.size() > 0)
			{
				for (vector<WorkerThread*>::const_iterator n = wThreads.begin(); n != wThreads.end(); ++n)
				{
					if ( (*n != nullptr) && ((*n)->GetStartTime() < oldestTime) )
					{
						wThread = *n;
						oldestTime = (*n)->GetStartTime();
					};
				};
			};
			return wThread;
		};

		void SendThread(WorkerThread *refThread) {
			lock_guard<mutex> lk1(sendCom); // No other thread may send
			unique_lock<mutex> lk2(mainCom); // Wait for main to signal that it's ready to handle the traffic
			threadAtt = refThread; // send thread
			cv.notify_one(); // Signal to main to continue
			cv.wait(lk2); // Allow main to continue and wait for main thread to finish (next wait() in main)
			// Release lock on sendCom, allow another thread to take traffic
		};

		void StartThread(WorkerThread *refThread) {
			refThread->status = 1;
			refThread->tHandle = new thread( &WorkerThread::Wrapper, refThread );
		};

		void RemoveThread(WorkerThread *refThread, vector<WorkerThread*> &workingThreads) {
			vector<WorkerThread*>::iterator pos = find(workingThreads.begin(), workingThreads.end(), refThread);
			if (pos != workingThreads.end()) // Valid Thread Pos
				*pos = nullptr;
		};

		bool CheckNewThread(WorkerThread *refThread, vector<WorkerThread*> &workingThreads)
		{
			vector<WorkerThread*>::iterator pos = find( workingThreads.begin(), workingThreads.end(), nullptr );
			if (pos != workingThreads.end()) {
				StartThread(refThread);
				*pos = refThread;
				return true;
			} else {return false;};
		};

		void MainThread()
		{
			vector<WorkerThread*> workingThreads( MAX_THREADS, nullptr );
			vector<WorkerThread*> waitingThreads;
			unique_lock<mutex> lk(mainCom);
			while (runMain)
			{
				WorkerThread *t1 = GetOldestWorker( workingThreads );
				{
					if (t1 != nullptr) {
						cv.wait_until(lk, t1->GetStartTime() + chrono::seconds( THREAD_TIMEOUT ));
					} else { 
						cv.wait(lk);
					};
				};
				if (threadAtt != nullptr) { // Process New / Finished Thread
					switch (threadAtt->status)
					{
					case 0:		// New Thread
						if ( !CheckNewThread(threadAtt, workingThreads) ) // Then add to waiting list
							waitingThreads.insert( waitingThreads.begin(), threadAtt );
						break;
					case 2:		// Finished Thread
						RemoveThread(threadAtt, workingThreads);
						finishedThreads.push_back(threadAtt);
						if ( (waitingThreads.size() > 0) && (CheckNewThread( waitingThreads.back(), workingThreads ) ))
							waitingThreads.pop_back();
						break;
					};
					threadAtt = nullptr;
					cv.notify_one();
				} else { // "Kill" t1 thread
					SetThreadPriority( (t1->tHandle)->native_handle(), THREAD_PRIORITY_IDLE ); // Set Idle
					RemoveThread(t1, workingThreads);
				};
			};
		};

		void WorkerThread::Wrapper()
		{
			this->result = this->func( this->params );
			this->status = 2;
			SendThread(this);
		};

		WorkerThread::WorkerThread( string(*function)( vector<string> &params ) )
		{
			this->status = -1;
			this->handle = threadCounter;
			++threadCounter;
			this->func = function;
		};

		WorkerThread::~WorkerThread()
		{
			if ((this->tHandle)->joinable())
				(this->tHandle)->join();
			delete this->tHandle;
		};

		unsigned int WorkerThread::Start( vector<string> &params )
		{
			this->params = params;
			this->startTime = chrono::system_clock::now();
			this->status = 0;
			SendThread(this);
			return this->handle;
		};
	};
};