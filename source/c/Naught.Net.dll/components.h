#pragma once

/* Definitions */

#define WORKER_IDLE_MIN 1 // Minimum number of idle workers.
#define WORKER_ALL_MAX 10 // Maximum number of active and idle workers.
#define WORKER_IDLE_TIMEOUT 300000 // Worker idle timeout in milliseconds, <= 0 for infinite.
#define WORKER_MAX_OPERATIONS 512 // Maximum number of operations a worker may perform before being destroyed (prevents memory leaks).

#define PKG_ACCESS_TIMEOUT 0 // Default package access mutex lock timeout in milliseconds, <= 0 for infinite.

#define RVE_INTERFACE_DELIM "~" // RVE (Arma) parameter delimiter for communication.
#define RVE_OUTPUT_ERROR "NAUGHT_NET_ERROR" // Output error message.
#define RVE_OUTPUT_EOF "NAUGHT_NET___EOF" // End of return/file.
#define RVE_OUTPUT_NULL "NAUGHT_NET__NULL" // Return nothing/null.

/* Naught.Net Components */

namespace ndt
{
	/* Templates */

	template<class T>
	struct Queue
	{
		std::mutex opLock;
		std::vector<T> contents;
	};

	/* Structs */

	struct Role
	{
		std::string name;
		bool forceAsync;
		std::function<std::string(std::vector<std::string>& args)> function;
	};

	/* Classes */

	class Package
	{
	private:
		std::timed_mutex pkgLock;
		// Consumable
		std::vector<std::string> contents;
		// Return
		bool readDone;
		std::string result;
		size_t resPos;
		// Functions
		bool authorize(int timeOut = PKG_ACCESS_TIMEOUT) {return this->pkgLock.try_lock_for(std::chrono::milliseconds(timeOut));};
		void deauthorize() {this->pkgLock.unlock();};
	public:
		Package(std::vector<std::string>& args); // Constructor
		~Package(); // Deconstructor
		void seal() {this->pkgLock.lock();};
		// Getter Methods
		const std::vector<std::string>& getContents() {return this->contents;};
		// Reader [Scanner] Methods
		const std::string& readResult(size_t blockSize);
		// Setter Methods
		void setResult(std::string& newResult) {this->result = newResult;};
	};

	class Scheduler
	{
	private:
		bool valid;
		Queue<Job*> jobQueue;
		Queue<Package*> outputQueue;
		std::atomic<size_t> workerCount;
		std::atomic<size_t> workerIdleCount;
		std::condition_variable workerIdling;
		// Functions
		Role* roleSearch(std::string& name); // TODO
		std::string schedule(std::vector<std::string>& args);
		void scheduleAsync(Job* job);
	public:
		Scheduler(); // Constructor
		~Scheduler(); // Deconstructor
		// Getter Methods
		bool isValid() {return this->valid;};
		Queue<Job*> getJobQueue() {return this->jobQueue;};
		Queue<Package*> getOutputQueue() {return this->outputQueue;};
		size_t getWorkerCount() {return this->workerCount;};
		size_t getWorkerIdleCount() {return this->workerIdleCount;};
		// Setter Methods
		void incWorkerCount() {++this->workerCount;};
		void decWorkerCount() {--this->workerCount;};
		void incWorkerIdleCount() {++this->workerIdleCount;};
		void decWorkerIdleCount() {--this->workerIdleCount;};
		// Functions
		bool workerIdle(std::unique_lock<std::mutex>& lk);
		std::string add(std::vector<std::string>& params);
		std::string addFromRVE(std::string& rvInput);
		std::string error(std::string text) {return (std::string(RVE_OUTPUT_ERROR) + std::string(RVE_INTERFACE_DELIM) + text);};
	};

	class Worker
	{
	private:
		Scheduler* scheduler;
		Job* curJob;
		// Functions
		void start();
	public:
		Worker(Scheduler* pSched); // Constructor
		~Worker(); // Deconstructor
	};

	class Job
	{
	private:
		Role* role;
		Package* pkg;
	public:
		// Getter Methods
		Role* getRole() {return this->role;};
		Package* getPackage() {return this->pkg;};
		// Functions
		Job(Role* pRole, Package* pPkg); // Constructor
		std::string start(Worker* worker); // TODO
	};

	class Interpreter // Static class, only static methods
	{
	public:
		static void stringToVector(std::string& input, std::vector<std::string>& output, std::string delim);
	};

};