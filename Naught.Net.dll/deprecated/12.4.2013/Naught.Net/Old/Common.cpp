#include "Common.h"

bool Common::ExecFunc(const string &function, vector<string> &params, string &result)
{
	bool setReturn = true;

	if (function == "Common_GetVersion")
	{
		result = Common::GetVersion();
	}
	else if (function == "Common_Test")
	{
		result = Common::Test( function, params );
	}
	else if (function == "Common_GetOutputChunks")
	{
		result = to_string(Common::GetOutputChunks(Globals::Result, Globals::OutputSize));
	}
	else if (function == "Common_PassTruncResult")
	{
		result = Common::PassTruncResult(params);
		setReturn = false;
	}
	else if ((function == "Strings_RegexMatch") && (params.size() > 1))
	{
		result = Strings::RegexMatch(params[0], params[1]);
	}
	else if ((function == "Strings_RegexSearch") && (params.size() > 1))
	{
		if (params.size() < 3)
			params[2] = "-1";
		result = Strings::RegexSearch(params[0], params[1], boost::lexical_cast<int,string>(params[2]));
	}
	else if ((function == "Strings_RegexReplace") && (params.size() > 2))
	{
		result = Strings::RegexReplace(params[0], params[1], params[2]);
	}
	else if ((function == "Strings_HashMD2") && (params.size() > 0))
	{
		result = Strings::Hash<CryptoPP::MD2>(params[0]);
	}
	else if ((function == "Strings_HashMD4") && (params.size() > 0))
	{
		result = Strings::Hash<CryptoPP::MD4>(params[0]);
	}
	else if ((function == "Strings_HashMD5") && (params.size() > 0))
	{
		result = Strings::Hash<CryptoPP::MD5>(params[0]);
	}
	else if ((function == "Strings_HashSHA1") && (params.size() > 0))
	{
		result = Strings::Hash<CryptoPP::SHA1>(params[0]);
	}
	else if ((function == "Strings_HashSHA256") && (params.size() > 0))
	{
		result = Strings::Hash<CryptoPP::SHA256>(params[0]);
	}
	else
	{
		setReturn = false;
	};

	return setReturn;
};

string Common::GetVersion()
{
	string version;
	switch (PLATFORM)
	{
		case 1:
			version += "Windows";
			break;
		case 2:
			version += "Macintosh";
			break;
		case 3:
			version += "Linux";
			break;
	};
	version += " ";
	version += SOFTWARE_VERSION;
	return version;
};

void Common::Truncate(string &result, const int &size)
{
	if (result.size() > (unsigned int) size)
	{
		int chunks = Common::GetOutputChunks(result, size);
		result = string(RETURN_TRUNC) + to_string(chunks);
	};
};

int Common::GetOutputChunks(const string &result, const int &size)
{
	return ((int) ceil(result.size() / size));
};

string Common::PassTruncResult(const vector<string> &params)
{
	if (params.size() > 0)
	{
		int chunk = boost::lexical_cast<int,string>(params[0]);
		int lower = Globals::OutputSize * chunk;
		int upper = min<int>((Globals::OutputSize * (chunk + 1)), Globals::Result.length());
		return Globals::Result.substr(lower, upper);
	}
	else
	{
		return RETURN_ERROR;
	};
};

string Common::Test(const string &function, const vector<string> &params)
{
	string result;
	result += function + string(" - ");
	result += Strings::VectorToArray(params);
	return result;
};