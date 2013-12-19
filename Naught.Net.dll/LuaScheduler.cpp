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
#include "IOHandler.h"
#include "LuaPackage.h"
#include "LuaScheduler.h"


LuaScheduler::LuaScheduler(void) {};

LuaScheduler::~LuaScheduler(void) {};

void LuaScheduler::newThread(LuaPackage* pkg)
{
	++activeTCount;
	new std::thread(threadProcess, this, pkg);
};

LuaPackage* LuaScheduler::requestNew()
{
	LuaPackage* newPkg = nullptr;
	std::unique_lock<std::mutex> lk(idleThread, std::defer_lock);
	threadQueue.wait_for(lk, std::chrono::milliseconds(THREAD_TIMEOUT), [this, &newPkg]() {
		execQueue.try_pop(newPkg);
	});
	return newPkg;
};

void LuaScheduler::threadProcess(LuaScheduler* scheduler, LuaPackage* pkg)
{
	bool run = true;
	while (pkg != nullptr)
	{
		/* Execute Lua Code */
		lua_State* L;
		int stat;
		do {
			pkg->open();
			L = pkg->getThread();
			stat = lua_resume(L, NULL, 0);
			if (stat == LUA_YIELD)
			{
				pkg->close();
				if (lua_tostring(L, -1) == "SQF_BREAK")
				{
					lua_pop(L, 1);
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
			if (stat == 0)
			{
				res = lua_tostring(L, -1);
			}
			else
			{
				res = ERRORMSG(lua_tostring(L, -1));
			};
			pkg->close();
			pkg = scheduler->finish(pkg);
		};
	};
	scheduler->threadExit();
};

void LuaScheduler::queuePackage(LuaPackage* pkg)
{
	execQueue.push(pkg);
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
	// TODO: Send finished package to IOHandler
	return requestNew();
};

void LuaScheduler::threadExit()
{
	--activeTCount;
};