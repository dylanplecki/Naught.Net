#include "stdafx.h"
#include "flags.h"
#include "package.h"
#include "distributer.h"
#include "worker.h"


void worker::start()
{
	while (true) {
		package* pkg = distributer::instance()->request();
		if (pkg)
		{
			pkg->resetFlags();
			if (jobs::jobList.count(pkg->getAddress()))
			{
				jobs::job job = jobs::jobList.at(pkg->getAddress());
				if (job.arguments == pkg->getArguments().size())
				{
					pkg->setContent( job.function(pkg->getArguments()) );
					pkg->setFlag(FLAG_GOOD);
				}
				else
				{
					pkg->setFlag(FLAG_ERROR);
					pkg->setContent("Passed arguments did not match expected function arguments.");
				};
			}
			else
			{
				pkg->setFlag(FLAG_ERROR);
				pkg->setContent("Specified internal function cannot be found.");
			};
			distributer::instance()->deliver(pkg);
		} else { break; };
	};
	/* End thread and delete worker */
	distributer::instance()->workerDetach(this); // Do not reference 'this' below this line
};


worker::worker()
{
	thread = new std::thread(&worker::start, this);
};


worker::~worker()
{
	if (thread)
		delete thread;
};