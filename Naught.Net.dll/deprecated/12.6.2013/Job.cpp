#include "stdafx.h"
#include "Role.h"
#include "Package.h"
#include "Worker.h"
#include "Job.h"


Job::Job(Role* pRole, Package* pPkg) : role(pRole), pkg(pPkg) {};

std::string Job::start(Worker* worker)
{

};