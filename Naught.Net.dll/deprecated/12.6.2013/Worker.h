#pragma once

class Job; // Forward Declaration

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