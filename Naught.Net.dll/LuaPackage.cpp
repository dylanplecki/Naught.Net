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
#include "LuaAPI.h"
#include "LuaPackage.h"


LuaPackage::LuaPackage(std::string ident, std::string code) : identity(ident), sourceCode(code), env(nullptr), thread(nullptr) {};

LuaPackage::~LuaPackage(void) {};

lua_State* LuaPackage::getEnv()
{
	if (env == nullptr)
	{
		/* Create New Lua State */
		env = LuaAPI::instance()->initState();
	};
	return env;
};

lua_State* LuaPackage::getThread()
{
	if (thread == nullptr)
	{
		/* Create New Lua Thread */
		LuaAPI::instance()->initThread(getEnv(), sourceCode);
	};
	return thread;
};

const std::string& LuaPackage::getIdentity()
{
	return identity;
};

const std::string& LuaPackage::getSource()
{
	return sourceCode;
};

bool LuaPackage::open()
{
	pkgLock.lock();
	return true;
};

bool LuaPackage::close()
{
	pkgLock.unlock();
	return true;
};

std::string& LuaPackage::edit()
{
	return result;
};

const std::string& LuaPackage::take(size_t& amount)
{
	size_t start = this->outputCounter;
	this->outputCounter += amount;
	return this->result.substr(start, this->outputCounter);
};

bool LuaPackage::isEmpty()
{
	return (outputCounter >= result.length());
};