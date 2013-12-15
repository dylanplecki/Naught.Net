#include "stdafx.h"
#include "Queue.h"
#include "Role.h"
#include "Interpreter.h"
#include "Package.h"
#include "Worker.h"
#include "Job.h"
#include "Scheduler.h"


std::string Scheduler::schedule(std::vector<std::string>& args)
{
	Role* role = this->roleSearch(args[0]);
	if (role != nullptr)
	{
		Job* job = new Job( role, new Package(args) );
		if (role->forceAsync || (boost::lexical_cast<bool,std::string>(args[1])))
		{ // Asynchronous Code
			std::thread t1(this->scheduleAsync, job);
			return RVE_OUTPUT_NULL;
		}
		else
		{ // Synchronous Code - Run it
			// TODO
		};
	} else {return this->error("No function match was found, role list exhausted.");};
};

void Scheduler::scheduleAsync(Job* job)
{
	std::lock_guard<std::mutex> lock(this->jobQueue.opLock);
	this->jobQueue.contents.push_back(job);
	while ((this->workerIdleCount < WORKER_IDLE_MIN) && (workerCount < WORKER_ALL_MAX))
	{
		new Worker(this);
	};
	if (this->workerIdleCount > 0) {this->workerIdling.notify_one();};
};

Scheduler::Scheduler() : valid(true) {};

bool Scheduler::workerIdle(std::unique_lock<std::mutex>& lk)
{
	return this->workerIdling.wait_for(lk, std::chrono::milliseconds(WORKER_IDLE_TIMEOUT), [this](){
		return this->getJobQueue().contents.size() > 0;
	});
};

std::string Scheduler::add(std::vector<std::string>& params)
{
	if (params.size() >= 2) // Function name and async bool
	{
		return this->schedule(params);
	} else {return this->error("Insufficient parameters provided to extension.");};
};

std::string Scheduler::addFromRVE(std::string& rvInput)
{
	std::vector<std::string> params;
	Interpreter::stringToVector(rvInput, params, RVE_INTERFACE_DELIM);
	this->add(params);
};