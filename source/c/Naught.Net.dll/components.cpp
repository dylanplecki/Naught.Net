#include "stdafx.h"
#include "components.h"

namespace ndt
{

	/* Job Class */



	/* Scheduler Class */

	std::string Scheduler::schedule(std::vector<std::string>& args)
	{
		if (args[0] == RVE_B_FUNC_GETVERSION)
		{
			return VER_FILE_VERSION_STR;
		}
		else if (args[0] == RVE_B_FUNC_GETRESULT)
		{
			// TODO - Truncation (Probably Last)
		}
		else if (args[0] == RVE_B_FUNC_TEST_EXT)
		{
			// TODO - Return Args
		}
		else if (args.size() >= 2)
		{
			Job* job = this->jobSearch(args[0]);
			if (job != nullptr)
			{
				Package* pkg = new Package(job, args);
				// TODO - Worker
			} else {return this->error("No function match was found, job list exhausted.");};
		};
		return this->error("Not enough parameters provided to extension and no basic function match.");
	};

	std::string Scheduler::add(std::string& rvInput)
	{
		std::vector<std::string> params;
		boost::split(params, rvInput, boost::is_any_of(RVE_INTERFACE_DELIM));
		if (params.size() >= 1)
		{
			return this->schedule(params);
		} else {return this->error("Not enough parameters provided to extension.");};
	};

	/* Package Class */

	Package::Package(Job* jobTitle, std::vector<std::string>& args)
	{
		this->job = jobTitle;
		this->async = boost::lexical_cast<bool,std::string>(args[1]);
		args.erase( args.begin(), (args.begin() + 1) ); // Removes jobTitle and async parameters
		this->params = args;
	};

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

	/* Worker Class */



};