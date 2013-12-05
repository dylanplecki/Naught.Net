#ifndef COMMON_H
#define COMMON_H

#include "Globals.h"
#include "Strings.h"

namespace Common
{
	bool ExecFunc(const string &function, vector<string> &params, string &result);
	string GetVersion();
	void Truncate(string &result, const int &size);
	int GetOutputChunks(const string &result, const int &size);
	string PassTruncResult(const vector<string> &params);
	string Test(const string &function, const vector<string> &params);
};

#endif