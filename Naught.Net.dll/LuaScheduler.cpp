/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

#include "stdafx.h"
#include "LuaPackage.h"
#include "LuaScheduler.h"
#include "IOHandler.h"


LuaScheduler::LuaScheduler() {};

LuaScheduler::~LuaScheduler() {};

void LuaScheduler::newThread()
{
	++activeTCount;
	//new std::thread(&LuaScheduler::threadProcess, this);
};

LuaPackage* LuaScheduler::requestNew()
{
	LuaPackage* newPkg = nullptr;
	while (newPkg == nullptr)
	{
		if (!execQueue.try_pop(newPkg))
		{
			std::unique_lock<std::mutex> lk(idleThread, std::defer_lock);
			++idleTCount;
			threadQueue.wait_for(lk, std::chrono::milliseconds(THREAD_TIMEOUT), [this, &newPkg] {
				return execQueue.try_pop(newPkg);
			});
			--idleTCount;
		};
		if (newPkg->execLock < std::chrono::steady_clock::now())
		{
			queuePackage(newPkg);
			newPkg = nullptr;
			std::this_thread::yield();
		};
	};
	return newPkg;
};

void LuaScheduler::threadProcess(LuaScheduler* scheduler)
{
	LuaPackage* pkg = requestNew();
	while (pkg != nullptr)
	{
		/* Execute Lua Code */
		lua_State* L;
		int stat;
		do {
			pkg->open();
			L = pkg->getThread();
			stat = lua_resume(L, NULL, pkg->luaArgCount());
			if (stat == LUA_YIELD)
			{
				pkg->close();
				std::string res = lua_tostring(L, -1);
				lua_settop (L, 0); // Remove all elements from stack
				if (res == "SQF_BREAK")
				{
					pkg = toss(pkg);
				}
				else
				{
					pkg = yield(pkg);
				};
			};
		} while ((pkg != nullptr) && (stat == LUA_YIELD));

		if (pkg != nullptr) // Finish execution
		{
			std::string& res = pkg->edit();
			res = lua_tostring(L, -1);
			if (stat != 0)
			{
				pkg->setFlag(PKG_FLAG_ERROR);
			};
			pkg->close();
			pkg = scheduler->finish(pkg);
		};
	};
	scheduler->threadExit();
};

bool LuaScheduler::search(std::string& ident, std::string& data)
{
	tbb::concurrent_hash_map<std::string,LuaPackage*>::const_accessor acc;
	if (waitingRoom.find(acc, ident))
	{
		LuaPackage* pkg = acc->second;
		waitingRoom.erase(acc);
		pkg->open();
		lua_pushstring(pkg->getThread(), data.c_str());
		pkg->luaArgCount(1);
		pkg->close();
		queuePackage(pkg);
		return true;
	} else {return false;};
};

void LuaScheduler::queuePackage(LuaPackage* pkg)
{
	execQueue.push(pkg);
	if ((idleTCount <= 0) && (activeTCount < MAX_THREADS))
	{
		newThread();
	};
	threadQueue.notify_one();
};

LuaPackage* LuaScheduler::yield(LuaPackage* pkg)
{
	queuePackage(pkg);
	return requestNew();
};

LuaPackage* LuaScheduler::toss(LuaPackage* pkg)
{
	waitingRoom.insert(std::pair<std::string,LuaPackage*>(pkg->getIdentity(),pkg));
	return requestNew();
};

LuaPackage* LuaScheduler::finish(LuaPackage* pkg)
{
	lua_close(pkg->getEnv());
	delete pkg->getEnv();
	IOHandler::instance()->queueOutput(pkg);
	return requestNew();
};

void LuaScheduler::threadExit()
{
	--activeTCount;
};