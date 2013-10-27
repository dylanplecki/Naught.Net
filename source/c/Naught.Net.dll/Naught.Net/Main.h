/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#ifndef MAIN_H
#define MAIN_H

// Macros
#define FUNCTION_0(fn, multiT, params) { #fn, fn, multiT, params }
#define FUNCTION_1(ns1, fn, multiT, params) { #fn, &ns1::fn, multiT, params }
#define FUNCTION_2(ns1, ns2, fn, multiT, params) { #fn, &ns1::ns2::fn, multiT, params }
#define EXT_FUNC_0(fn, multiT, params) FUNCTION_1(External, fn, multiT, params)
#define EXT_FUNC_1(ns1, fn, multiT, params) FUNCTION_2(External, ns1, fn, multiT, params)

#include "Globals.h"
#include "Internal.h"
#include "External.h"

struct Function {
	string name;
	string (*func)( vector<string> &params );
	bool threaded;
	unsigned int params;
};

static Function ExtFunctionsArray[] = {
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
	{"Download",		External::Network::Download,						true,	1	}
};

static vector<Function> ExtFunctions(ExtFunctionsArray, (ExtFunctionsArray + (sizeof(ExtFunctionsArray) / sizeof(Function))) );

string Init();
string CallFunc( string &sFunc, vector<string> &params );

#endif