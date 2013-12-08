#include "stdafx.h"
#include "components.h"

namespace ndt
{

	/* Package Class */

	Package::Package(std::vector<std::string>& args) : contents(args) {};

	const std::string& Package::readResult(size_t blockSize)
	{
		size_t prevBlock = this->resPos;
		this->resPos += blockSize;
		if (this->resPos >= this->result.length())
		{
			this->readDone = true;
		};
		return this->result.substr(prevBlock, blockSize);
	};

	/* Scheduler Class */

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

	/* Worker Class */

	void Worker::start()
	{
		bool die = false;
		for (int i = 0; i < WORKER_MAX_OPERATIONS; ++i) {
			std::unique_lock<std::mutex> lk1(this->scheduler->getJobQueue().opLock);
			if (this->scheduler->getJobQueue().contents.size() == 0)
			{
				this->scheduler->incWorkerIdleCount();
				if (!this->scheduler->workerIdle(lk1))
					die = true;
				this->scheduler->decWorkerIdleCount();
			};
			if (!die && this->scheduler->isValid())
			{ // Process Job
				this->curJob = this->scheduler->getJobQueue().contents.front();
				this->scheduler->getJobQueue().contents.erase(this->scheduler->getJobQueue().contents.begin());
				lk1.unlock();

			} else break;
		};
		delete this;
	};

	Worker::~Worker()
	{
		if (curJob != nullptr)
		{
			delete curJob;
		};
		this->scheduler->decWorkerCount();
	};

	Worker::Worker(Scheduler* pSched) : scheduler(pSched), curJob(nullptr)
	{
		this->scheduler->incWorkerCount();
		std::thread t1(this->start, 0);
	};

	/* Job Class */

	Job::Job(Role* pRole, Package* pPkg) : role(pRole), pkg(pPkg) {};

	std::string Job::start(Worker* worker)
	{

	};

	/* Interpreter Class */

	void Interpreter::stringToVector(std::string& input, std::vector<std::string>& output, std::string delim)
	{
		boost::split(output, input, boost::is_any_of(delim));
	};

};