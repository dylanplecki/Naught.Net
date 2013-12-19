/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

#pragma once

#define MAX_THREADS 24
#define THREAD_TIMEOUT 120000 // milliseconds

/*
	Class: LuaScheduler
	Objective:
		To receive input packages and process them with
		a unique and parallel Lua environment.
*/
class LuaScheduler
{
private:
	std::mutex idleThread;
	std::atomic<size_t> activeTCount;
	std::condition_variable threadQueue;
	tbb::concurrent_queue<LuaPackage*> execQueue;
	tbb::concurrent_hash_map<std::string,LuaPackage*> waitingRoom;
	void newThread(LuaPackage* pkg);
	LuaPackage* requestNew();
protected:
	void threadProcess(LuaScheduler* scheduler, LuaPackage* pkg);
public:
	LuaScheduler(void);
	~LuaScheduler(void);
	bool search(std::string& ident, std::string& data);
	void queuePackage(LuaPackage* pkg);
	// Internal Threading Library
	LuaPackage* yield(LuaPackage* pkg); // Yields a LuaPackage for another, sends first to bottom of execQueue
	LuaPackage* toss(LuaPackage* pkg); // Tosses a LuaPackage for another, sends first to waitingRoom
	LuaPackage* finish(LuaPackage* pkg); // Finishes a LuaPackage, asks for another
	void threadExit();
};