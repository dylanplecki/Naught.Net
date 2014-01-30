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

/* Package Flags */

#define PKG_FLAG_NORMAL 0
#define PKG_FLAG_ERROR 1
#define PKG_FLAG_CODE 2

class LuaPackage
{
private:
	int pkgFlag;
	size_t luaArgs;
	lua_State* env;
	lua_State* thread;
	std::mutex pkgLock;
	std::string result;
	size_t outputCounter;
	std::string identity;
	std::string sourceCode;
public:
	std::chrono::time_point<std::chrono::steady_clock::time_point::clock, std::chrono::milliseconds> execLock; // Cannot execute until this timepoint
	LuaPackage(std::string ident, std::string code);
	~LuaPackage();
	// Get methods
	int getFlag() {return pkgFlag;};
	lua_State* getEnv();
	lua_State* getThread();
	const std::string& getIdentity();
	const std::string& getSource();
	// Set methods
	void setFlag(int flg) {pkgFlag = flg;};
	// Object interaction
	bool open();
	bool close();
	std::string& edit();
	const std::string take(size_t& amount);
	bool isEmpty();
	size_t luaArgCount();
	void luaArgCount(size_t count);
};