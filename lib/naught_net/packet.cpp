#include "stdafx.h"
#include "flags.h"
#include "packet.h"


std::string packet::getFlags()
{
	return flags.to_string();
};


void packet::setFlag(size_t pFlag, bool pSwitch = true)
{
	flags.set(pFlag, pSwitch);
};


bool packet::checkFlag(size_t flag)
{
	return flags[flag];
};


void packet::resetFlags()
{
	flags.reset();
};


size_t packet::getId()
{
	return id;
};


std::string packet::getAddress()
{
	return address;
};


std::string packet::getContent()
{
	return content;
};


void packet::setAddress(std::string &pAddr)
{
	address = pAddr;
};


void packet::setContent(std::string pContent)
{
	content = pContent;
};