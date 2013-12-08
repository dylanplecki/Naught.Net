#pragma once

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