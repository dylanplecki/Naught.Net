#include "stdafx.h"
#include "LuaAPI.h"


LuaAPI *LuaAPI::s_instance = 0;

lua_State* LuaAPI::initState()
{
	/* Create New Lua State */
	lua_State* env = luaL_newstate();

	/* Load Lua Libraries */
	luaL_requiref(env, "_G", luaopen_base, true);
	luaL_requiref(env, "coroutine", luaopen_coroutine, true);
	luaL_requiref(env, "string", luaopen_string, true);
	luaL_requiref(env, "table", luaopen_table, true);
	luaL_requiref(env, "math", luaopen_math, true);
	luaL_requiref(env, "bit32", luaopen_bit32, true);

	/* Load Internal Lua Functions */
	// TODO

	return env;
};

lua_State* LuaAPI::initThread(lua_State* state, std::string& src)
{
	/* Create New Lua Thread */
	lua_State* thread = lua_newthread(state);

	/* Load Initial Lua Code Package */
	luaL_loadstring(thread, src.c_str());

	return thread;
};