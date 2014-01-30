#pragma once

#include "packet.h"

#define ARGUMENT_DELIM "~"

class package : public packet // Interactive and self-sustaining packet
{
private:
	/* States */
	size_t placeholder;
	std::vector<std::string> arguments;
	/* Non-Characteristics */
	static size_t id_counter;
	/* Functions */
	std::vector<std::string> filterArguments(std::string &args);
public:
	/* Constructors */
	package();
	package(std::string &pkt);
	/* Getter Behaviors */
	std::vector<std::string>& getArguments() { return arguments; };
	bool getContent(std::string &container, size_t size);
	/* Setter Behaviors */
	void setArguments(std::vector<std::string>& args) { arguments = args; };
};

size_t package::id_counter = 1;