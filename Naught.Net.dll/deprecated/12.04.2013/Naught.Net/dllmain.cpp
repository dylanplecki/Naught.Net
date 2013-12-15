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

	if (string(function) == "Initialization") {result = Main::Init();} else {
		if (Initialization)
		{
			vector<string> arguments = Internal::Strings::SplitString(string(function), FUNC_DELIMETER, 1);
			vector<string> parameters;

			if (arguments.size() > 1)
				parameters = Internal::Strings::SplitString(arguments[1], PARAM_DELIMETER);

			result = Main::CallFunc( arguments[0], parameters );

			Internal::TruncateString(result, curOutputSize);
		} else {result = Internal::ErrorMessage("Initialization has not been called.");};
	};

	strncpy( output, result.c_str(), curOutputSize );
};

namespace Main
{
	Function ExtFunctionsArray[] = {
		{"GetVersion",		External::GetVersion,								false,	0	},
		{"Test",			External::Test,										false,	0	},
		{"ReturnData",		External::ReturnData,								false,	1	},
		{"GetResultChunk",	External::GetResultChunk,							false,	2	},
		{"RegexMatch",		External::Strings::RegexMatch,						false,	2	},
		{"RegexSearch",		External::Strings::RegexSearch,						false,	2	},
		{"RegexReplace",	External::Strings::RegexReplace,					false,	3	},
		{"HashMD2",			External::Strings::HashString<CryptoPP::MD2>,		false,	1	},
		{"HashMD4",			External::Strings::HashString<CryptoPP::MD4>,		false,	1	},
		{"HashMD5",			External::Strings::HashString<CryptoPP::MD5>,		false,	1	},
		{"HashSHA1",		External::Strings::HashString<CryptoPP::SHA1>,		false,	1	},
		{"HashSHA256",		External::Strings::HashString<CryptoPP::SHA256>,	false,	1	},
		{"ParseXML",		External::Data::ParseXML,							false,	1	},
		{"Download",		External::Network::Download,						true,	1	}
	};

	vector<Function> ExtFunctions(ExtFunctionsArray, (ExtFunctionsArray + (sizeof(ExtFunctionsArray) / sizeof(Function))) );

	string Init()
	{
		if (!Initialization) {
			Initialization = true;

			string configPath = Internal::GetCurDir() + string(CONFIG_FILE);
			fstream config(configPath);

			if (!config.good()) { // Create New File
				Main::CreateConfig(config);
			};

			if (config.good()) { // Read File

			};

			thread *main = new thread(Internal::Threading::MainThread); // Launch Main Thread
		};

		vector<string> params; // Empty Value
		return External::GetVersion(params);
	};

	string CallFunc(string &sFunc, vector<string> &params)
	{
		vector<Main::Function>::iterator i = Main::ExtFunctions.begin();
		string result;
		while (i != Main::ExtFunctions.end()) {
			if ((*i).name == sFunc)
				break;
			++i;
		};
		if ((i != Main::ExtFunctions.end()) && (params.size() >= (*i).params)) {
			if ((*i).threaded) {
				Internal::Threading::WorkerThread *t1 = new Internal::Threading::WorkerThread( (*i).func );
				result = string(RETURN_HANDLE) + string(PARAM_DELIMETER) + to_string(t1->Start(params));
			} else {
				result = (*i).func(params);
			};
		} else {result = Internal::ErrorMessage("Function Not Found.");};
		return result;
	};

	void CreateConfig(fstream &config)
	{
		HINSTANCE hInst = GetModuleHandle(NULL);
		HRSRC hRes = FindResource(hInst, MAKEINTRESOURCE(DFT_CONFIG), L"TEXT");
		HGLOBAL hMem = LoadResource(hInst, hRes);
		config << (char*)LockResource(hMem);
		config.flush();
		FreeResource(hMem);
	};
};