#pragma once

/* Definitions */

#define PKG_ACCESS_TIMEOUT 0 // Default package access mutex lock timeout in milliseconds

#define RVE_INTERFACE_DELIM "~"

#define RVE_B_FUNC_GETVERSION "version"
#define RVE_B_FUNC_GETRESULT "result"
#define RVE_B_FUNC_TEST_EXT "test"

#define RVE_OUTPUT_ERROR "NAUGHT_NET_ERROR"
#define RVE_OUTPUT_TRUNCATED "NAUGHT_NET_TRUNC"
#define RVE_OUTPUT_HANDLE "NAUGHT_NET_HANDL"
#define RVE_OUTPUT_NULL "NAUGHT_NET__NULL"

namespace ndt
{

	/* Classes */

	class Job
	{
	private:
		bool forceAsync;
		std::string jobFunc();
	public:
		std::string start(Package& pkg);
	};

	class Scheduler
	{
	private:
		Job* jobSearch(std::string& jobTitle); // TODO
		std::string schedule(std::vector<std::string>& args);
	public:
		std::string add(std::string& rvInput);
		std::string error(std::string text) {return (std::string(RVE_OUTPUT_ERROR) + std::string(RVE_INTERFACE_DELIM) + text);};
	};

	class Package
	{
	private:
		std::timed_mutex pkgLock;
		// Consumable Contents
		bool async;
		Job* job;
		std::vector<std::string> params;
		// Return Contents
		bool readDone;
		std::string result;
		size_t resPos;
		// Functions
		bool authorize(int timeOut = PKG_ACCESS_TIMEOUT) {return this->pkgLock.try_lock_for(std::chrono::milliseconds(timeOut));};
		void deauthorize() {this->pkgLock.unlock();};
	public:
		Package(Job* pJobTitle, std::vector<std::string>& args); // Constructor
		void seal() {this->pkgLock.lock();};
		// Getter Methods
		const bool& getAsync() {return this->async;};
		const Job* getJobTitle() {return this->job;};
		const std::vector<std::string>& getParameters() {return this->params;};
		// Reader [Scanner] Methods
		const std::string& readResult(size_t blockSize);
		// Setter Methods
		void setResult(std::string& newResult) {this->result = newResult;};
	};

	class Worker
	{
	private:

	};

};