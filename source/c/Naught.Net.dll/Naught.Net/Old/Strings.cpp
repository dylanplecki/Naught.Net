#include "Strings.h"

char* Strings::GetNonConstStr(const string &s)
{
	static std::vector<char> var;
	var.assign(s.begin(),s.end());
	var.push_back('\0');
	return &var[0];
};

vector<string> Strings::SplitString(const string &function, string delimeter)
{
	int i = function.find(delimeter);
	vector <string> v;
	if (i != string::npos)
	{
		v.push_back( function.substr( 0, i ) );
		if (function.length() > (unsigned int) i)
		{
			v.push_back( function.substr( (i + 1), function.length() ) );
		};
	}
	else
	{
		v.push_back( function );
	};
	return v;
};

vector<string> Strings::SplitParams(const string &params, string delimeter)
{
	vector <string> v;
	int i = 0;
	int start = 0;
	do {
		i = params.find(delimeter, i);
		if (i != string::npos)
		{
			if (i > 0)
				v.push_back( params.substr( start, (i - start) ) );
			i += delimeter.length();
			start = i;
		}
		else
		{
			v.push_back(params.substr(start, params.length()));
		};
	} while ((i != string::npos) && ((unsigned int) i <= params.length()));
	return v;
};

string Strings::VectorToArray(const vector<string> &v)
{
	string result = "[";
	for (vector<string>::const_iterator n = v.begin(); n != v.end(); ++n)
	{
		if (n != v.begin())
			result += ",";
		result += string("\"") + *n + string("\"");
	};
	result += "]";
	return result;
};

string Strings::SMatchToArray(const smatch &m)
{
	string result = "[";
	int i = 0;
	for (auto x:m)
	{
		if (i != 0)
			result += ",";
		result += string("\"") + x.str() + string("\"");
		++i;
	}
	result += "]";
	return result;
};

string Strings::RegexMatch(const string &subject, const string &pattern)
{
	string result = "false";
	if (regex_match(subject, regex(pattern)))
		result = "true";
	return result;
};

string Strings::RegexSearch(string subject, const string &pattern, int maxi)
{
	smatch m;
	string result = "[";
	int i = 0;
	while (regex_search(subject, m, regex(pattern)) && ((maxi == -1) || (i < maxi)))
	{
		if (i != 0)
			result += ",";
		result += Strings::SMatchToArray(m);
		subject = m.suffix().str();
		++i;
	}
	result += "]";
	return result;
};

string Strings::RegexReplace(string subject, const string &pattern, const string &replace)
{
	return regex_replace(subject, regex(pattern), replace);
};

string Strings::FromBool(bool value)
{
	if (value)
		return "true";
	else
		return "false";
};