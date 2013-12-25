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