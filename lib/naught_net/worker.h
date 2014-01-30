#pragma once

class worker // Bare class for now
{
private:
	std::thread* thread;
	void start();
public:
	worker();
	~worker();
	std::thread* getThread();
};

namespace jobs
{
	struct job
	{
		std::function<std::string(std::vector<std::string> &args)> function;
		bool async;
		size_t arguments;
	};

	std::unordered_map<std::string,job> jobList = {
		// { "jobName", { jobFunc, asyncBool, argCountInt } },
		{ "jobName", { jobFunc, false, 0 } },
	};

	std::string jobFunc(std::vector<std::string> &args);
};