/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#include "Main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	};
	return TRUE;
};

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function); 
};

void __stdcall RVExtension(char *output, int outputSize, const char *function)
{
	curOutputSize = outputSize;
	curOutputSize -= 1;
	string result;

	if (string(function) == "Initialization") {result = Init();} else {
		if (Initialization)
		{
			vector<string> arguments = Internal::Strings::SplitString(string(function), FUNC_DELIMETER, 1);
			vector<string> parameters;

			if (arguments.size() > 1)
				parameters = Internal::Strings::SplitString(arguments[1], PARAM_DELIMETER);

			result = CallFunc( arguments[0], parameters );

			Internal::TruncateString(result, curOutputSize);
		} else {result = Internal::ErrorMessage("Initialization has not been called.");};
	};

	strncpy( output, result.c_str(), curOutputSize );
};

string Init()
{
	if (!Initialization) {
		Initialization = true;
		thread *main = new thread(Internal::Threading::MainThread); // Launch Main Thread
	};
	vector<string> params; // Empty Value
	return External::GetVersion(params);
};

string CallFunc( string &sFunc, vector<string> &params )
{
	vector<Function>::iterator i = ExtFunctions.begin();
	string result;
	while (i != ExtFunctions.end()) {
		if ((*i).name == sFunc)
			break;
		++i;
	};
	if ((i != ExtFunctions.end()) && (params.size() >= (*i).params)) {
		if ((*i).threaded) {
			Internal::Threading::WorkerThread *t1 = new Internal::Threading::WorkerThread( (*i).func );
			result = string(RETURN_HANDLE) + string(PARAM_DELIMETER) + to_string(t1->Start(params));
		} else {
			result = (*i).func(params);
		};
	} else {result = Internal::ErrorMessage("Function Not Found.");};
	return result;
};