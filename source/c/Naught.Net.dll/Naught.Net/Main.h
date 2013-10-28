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

#include "Globals.h"
#include "Internal.h"
#include "External.h"
#include "resource.h"

namespace Main
{
	struct Function {
		string name;
		string (*func)( vector<string> &params );
		bool threaded;
		unsigned int params;
	};

	extern Function ExtFunctionsArray[];
	extern vector<Function> ExtFunctions;

	string Init();
	string CallFunc(string &sFunc, vector<string> &params);
	void CreateConfig(fstream &config);
};

#endif