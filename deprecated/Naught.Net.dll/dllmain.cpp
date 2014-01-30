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
#include "dllmain.h"

HMODULE luaLib;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		luaLib = LoadLibrary(s2ws(getCurDir() + "lua\\lua32.dll").c_str());
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		FreeLibrary(luaLib);
		break;
	};
	return TRUE;
};

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *inputString); 
};

void __stdcall RVExtension(char *output, int outputSize, const char *inputString)
{
	outputSize -= 1;
	strncpy(output, IOHandler::instance()->receiveInput(inputString, outputSize).c_str(), outputSize);
};

std::string getCurDir()
{
	char path[MAX_PATH];
	HMODULE hm = NULL;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR) &getCurDir, &hm);
	GetModuleFileNameA(hm, path, sizeof(path));
	std::string ret = path;
	return (ret.substr(0, ret.find_last_of('\\')) + '\\');
};

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
};