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


class LuaAPI
{
private:
	static LuaAPI *s_instance;
	int setPackagePath(lua_State* L, std::string pType, std::string path);
public:
	lua_State* initState();
	lua_State* initThread(lua_State* state, std::string& src);

	/* RVE API Functions */
	

	/* Singleton Function */
	static LuaAPI *instance()
    {
        if (!s_instance)
			s_instance = new LuaAPI;
        return s_instance;
    };
};