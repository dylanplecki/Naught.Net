#pragma once

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