/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#include "External.h"

namespace External
{
	string GetVersion( vector<string> &params )
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

	string Test(vector<string> &params)
	{
		return Internal::Strings::VectorToSQF(params);
	};

	string ReturnData(vector<string> &params)
	{
			unsigned int threadHandle = boost::lexical_cast<unsigned int,string>(params[0]);
			Internal::Threading::WorkerThread *wThread = Internal::Threading::RetrieveFinishedThread(threadHandle, true);
			if ((wThread != nullptr) && (wThread->status == 2)) {
				string result = wThread->result;
				delete wThread;
				return result;
			} else {return RETURN_NULL;};
	};

	string GetResultChunk(vector<string> &params)
	{
		int resultHandle = boost::lexical_cast<int,string>(params[0]);
		int chunk = boost::lexical_cast<int,string>(params[1]);
		return Internal::GetTruncChunks(resultHandle, chunk);
	};

	namespace Strings
	{
		string RegexMatch(vector<string> &params)
		{
			string result = "false";
			if (regex_match(params[0], regex(params[1])))
				result = "true";
			return result;
		};

		string RegexSearch(vector<string> &params)
		{
			smatch m;
			string subject = params[0];
			int maxi = -1;
			if (params.size() > 2)
				maxi = boost::lexical_cast<int,string>(params[2]);
			string result = "[";
			int i = 0;
			while (regex_search(subject, m, regex(params[1])) && ((maxi == -1) || (i < maxi)))
			{
				if (i != 0)
					result += ",";
				result += Internal::Strings::SMatchToSQF(m);
				subject = m.suffix().str();
				++i;
			}
			result += "]";
			return result;
		};

		string RegexReplace(vector<string> &params)
		{
			return regex_replace(params[0], regex(params[1]), params[2]);
		};
	};

	namespace Data
	{
		string ParseXML(vector<string> &params)
		{
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load( (params[0]).c_str() );
			if (result) {
				return Internal::Data::XML::NodeToSQF(doc);
			} else {return Internal::ErrorMessage("XML source parsed with errors; aborted.");};
		};

		string ParseYAML(vector<string> &params)
		{
			YAML::Node node = YAML::Load( params[0] );

			return "";
		};
	};

	namespace Network
	{
		string Download(vector<string> &params)
		{
			CURL *curl;
			CURLcode res;
			string result;
			int timeOut = HTTP_CON_TIMEOUT;
			curl_global_init(CURL_GLOBAL_ALL);
			curl = curl_easy_init();
			if (curl) {
				if (params.size() > 1) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params[1]);
				if (params.size() > 2) timeOut = boost::lexical_cast<int,string>(params[2]);

				curl_easy_setopt(curl, CURLOPT_URL, params[0]);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlDownload::WriteData);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
				curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, CurlDownload::Progress);
				curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOut);

				res = curl_easy_perform(curl);
				curl_easy_cleanup(curl);
			} else {result = Internal::ErrorMessage("CURL Initialization Failed.");};
			curl_global_cleanup();
			return result;
		};

		namespace CurlDownload
		{
			size_t WriteData(char *ptr, size_t size, size_t nmemb, string *userdata)
			{
				size_t dataSize = size * nmemb;
				size_t bytesLeft = HTTP_MAX_CON_WRITE - (userdata->size() + dataSize);
				size_t bytesWritten = min(bytesLeft, dataSize);
				*userdata += string(ptr).substr(0, bytesWritten);
				return bytesWritten;
			};

			int Progress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
			{
				if ((dlnow <= HTTP_MAX_CON_DOWNLOAD) && (ulnow <= HTTP_MAX_CON_UPLOAD)) {
					return 0;
				};
				return 1; // Terminate Connection
			};
		};
	};
};