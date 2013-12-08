#ifndef NETWORK_H
#define NETWORK_H

#include "Globals.h"

namespace Network
{
	static int GlobalConnections = 0;
	static int HandleCounter = 0;
	static vector<Connection> CurrentConnections;
	static vector<Connection> WaitingConnections;

	class Connection
	{
	protected:
		int handle;
		string address;
		string postData;
		bool connected;
		thread::id threadID;
		string result;
		size_t WriteData( char *ptr, size_t size, size_t nmemb, void *userdata);
		int Progress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
		void Connect();
	public:
		Connection(string addr, string post = "");
		~Connection();
		bool Connected() {return this->connected;};
		string Address() {return this->address;};
		string PostData() {return this->postData;};
		void Address(string addr) {this->address = addr;};
		void PostData(string post) {this->postData = post;};
		void StartThread(bool newThread);
		bool SendRequest();
		bool Terminate();
		string GetResult();
	};
};

#endif