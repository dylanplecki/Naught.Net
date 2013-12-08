#pragma once

struct Role
{
	std::string name;
	bool forceAsync;
	std::function<std::string(std::vector<std::string>& args)> function;
};