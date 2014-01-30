#include "stdafx.h"
#include "package.h"


package::package() : placeholder(0)
{
	id = id_counter;
	++id_counter;
};


package::package(std::string &pkt) : package()
{
	flags = boost::lexical_cast<size_t>(pkt.substr(PACKET_FLAG_START, PACKET_FLAG_LEN));
	// Skip id = packet.substr(PACKET_IDEN_START, PACKET_IDEN_LEN);
	address = pkt.substr(PACKET_ADDR_START, PACKET_ADDR_LEN);
	arguments = filterArguments(pkt.substr(PACKET_CONT_START, PACKET_CONT_LEN));
};

std::vector<std::string> filterArguments(std::string &args)
{
	std::vector<std::string> ret;
	boost::split(ret, args, boost::is_any_of(ARGUMENT_DELIM));
	return ret;
};


bool package::getContent(std::string &container, size_t size)
{
	container = content.substr(placeholder, size);
	placeholder += size;
	return (placeholder >= content.size());
};