#include "Network.h"

namespace Network
{
	/* Connection Class */

	Connection::Connection(string addr, string post)
	{
		handle = HandleCounter;
		++HandleCounter;
		address = addr;
		postData = post;
	};

	Connection::~Connection() {};

	size_t Connection::WriteData( char *ptr, size_t size, size_t nmemb, void *userdata)
	{
		result += string(ptr);
		return size;
	};

	int Connection::Progress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
	{
		if (connected) {
			if ((dlnow <= MAX_CONNECTION_DOWNLOAD) && (ulnow <= MAX_CONNECTION_UPLOAD))
				return 0;
		};
		return 1; // Terminate Connection
	};

	void Connection::Connect()
	{
		CURL *curl;
		CURLcode res; 
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, address);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Progress);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
			result = "";
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			connected = false;
			if (WaitingConnections.size() > 0) {
				Connection connection = WaitingConnections.back();
				WaitingConnections.pop_back();
				connection.StartThread(false);
			} else {
				--(Network::GlobalConnections);
			};
		};
		curl_global_cleanup();
	};

	void Connection::StartThread(bool newThread)
	{
		if (newThread)
			++(Network::GlobalConnections);
		connected = true;
		thread t1( &Connection::Connect );
		threadID = t1.get_id();
	};

	bool Connection::SendRequest()
	{
		if (!(this->connected)) {
			// New Connection
			if (Network::GlobalConnections < MAX_HTTP_CONNECTIONS) {
				StartThread(true);
			} else {
				WaitingConnections.insert( WaitingConnections.begin(), this );
			};
		} else {
			return false;
		};
	};

	bool Connection::Terminate()
	{
		if (connected) {
			connected = false;
		};
		return true;
	};

	string Connection::GetResult()
	{
		if (!connected) {
			return result;
		} else {
			return RETURN_NULL;
		};
	};

	/* End Connection Class */
	/* Networking Functions */

	string NewConnection(string addr, string post = "")
	{
		Connection* newCon = new Connection(addr, post);
	};


};