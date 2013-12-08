#include "stdafx.h"
#include "Scheduler.h"
#include "Worker.h"


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