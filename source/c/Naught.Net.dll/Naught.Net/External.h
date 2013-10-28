/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "Globals.h"
#include "Internal.h"

namespace External
{
	string GetVersion(vector<string> &params);
	string Test(vector<string> &params);
	string ReturnData(vector<string> &params);
	string GetResultChunk(vector<string> &params);

	namespace Strings
	{
		string RegexMatch(vector<string> &params);
		string RegexSearch(vector<string> &params);
		string RegexReplace(vector<string> &params);

		template <class type>
		string HashString(vector<string> &params)
		{
			return Internal::Strings::Hash<type>(params[0]);
		};
	};

	namespace Data
	{
		string ParseXML(vector<string> &params);
	};

	namespace Network
	{
		string Download(vector<string> &params);
		namespace CurlDownload
		{
			size_t WriteData(char *ptr, size_t size, size_t nmemb, string *userdata);
			int Progress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
		};
	};
};

#endif