/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#ifndef INTERNAL_H
#define INTERNAL_H

#include "Globals.h"

namespace Internal
{
	struct SavedResult {
		unsigned int handle;
		size_t chunkSize;
		int chunks;
		string result;
	};

	extern unsigned int SavedResultCounter;
	extern vector<SavedResult> SavedResults;

	string ErrorMessage(string message);
	void TruncateString(string &s, const int &size);
	int CountTruncChunks(const string &s, const int &size);
	string GetTruncChunks(int resultHandle, int chunk);
	void ThreadWrapper(vector<string> &params);

	namespace Strings
	{
		char* GetNonConstStr(const string &s);
		vector<string> SplitString(const string &s, const string &delim, int maxi = -1);
		string BoolToString(const bool &value);
		string VectorToSQF(const vector<string> &v);
		string SMatchToSQF(const smatch &m);

		template <class type>
		string Hash(const string &text)
		{
			using namespace CryptoPP;
			string output;
			type hash;
			StringSource ss(text, true,
				new HashFilter(hash,
					new HexEncoder (
						new StringSink(output))));
			return output;
		};
	};

	namespace Threading
	{
		class WorkerThread
		{
		protected:
			chrono::steady_clock::time_point startTime;
			string (*func)( vector<string> &params );
			vector<string> params;
		public:
			unsigned int handle;
			thread *tHandle;
			int status;			// 0=new, 1=working, 2=finished
			string result;
			WorkerThread( string(*function)( vector<string> &params ) );
			~WorkerThread();
			unsigned int Start( vector<string> &params );
			void Wrapper();
			chrono::steady_clock::time_point GetStartTime() {return this->startTime;};
		};

		extern bool runMain; // Main Thread Loop Check
		extern unsigned int threadCounter;
		extern WorkerThread *threadAtt;
		extern vector<WorkerThread*> finishedThreads;

		WorkerThread* RetrieveFinishedThread(unsigned int threadHandle, bool removeThread = false);
		WorkerThread* GetOldestWorker(vector<WorkerThread*> &wThreads);
		void SendThread(WorkerThread *refThread);
		void StartThread(WorkerThread* refThread);
		void RemoveThread(vector<WorkerThread*>);
		bool CheckNewThread(WorkerThread *refThread, vector<WorkerThread*> &workingThreads);
		void MainThread();
	};
};

#endif