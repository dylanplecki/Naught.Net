#include "stdafx.h"
#include "Package.h"


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