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


class LuaPackage
{
private:
	lua_State* env;
	lua_State* thread;
	std::mutex pkgLock;
	std::string result;
	size_t outputCounter;
	std::string identity;
	std::string sourceCode;
	std::chrono::steady_clock::time_point execLock;
public:
	LuaPackage(std::string ident, std::string code);
	~LuaPackage(void);
	// Get methods
	lua_State* getEnv();
	lua_State* getThread();
	const std::string& getIdentity();
	const std::string& getSource();
	// Object interaction
	bool open();
	bool close();
	std::string& edit();
	const std::string& take(size_t& amount);
	bool isEmpty();
};