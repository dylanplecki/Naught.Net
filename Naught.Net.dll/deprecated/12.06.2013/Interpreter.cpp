#include "stdafx.h"
#include "Interpreter.h"


void Interpreter::stringToVector(std::string& input, std::vector<std::string>& output, std::string delim)
{
	boost::split(output, input, boost::is_any_of(delim));
};