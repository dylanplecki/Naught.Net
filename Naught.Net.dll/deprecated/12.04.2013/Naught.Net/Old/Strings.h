#ifndef STRINGS_H
#define STRINGS_H

#include "Globals.h"

namespace Strings
{
	// Templates
	template <class type>
	string Hash(const string &text)
	{
		using namespace CryptoPP;
		string output;
		type hash;
		StringSource ss(text, true,
			new HashFilter(hash,
				new HexEncoder (
					new StringSink(output))));
		return output;
	};

	// Functions
	char* GetNonConstStr(const std::string &s);
	vector<string> SplitString(const string &function, string delimeter);
	vector<string> SplitParams(const string &params, string delimeter);
	string VectorToArray(const vector<string> &v);
	string SMatchToArray(const smatch &m);
	string RegexMatch(const string &subject, const string &pattern);
	string RegexSearch(string subject, const string &pattern, int maxi);
	string RegexReplace(string subject, const string &pattern, const string &replace);
	string FromBool(bool value);
};

#endif