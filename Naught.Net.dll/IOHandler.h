/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

#pragma once

class IOHandler
{
private:
	std::mutex extIO;
	Queue<LuaPackage*> outputQueue;
	std::vector<LuaScheduler*> schedulers;
	std::unordered_map<std::string,LuaPackage*> pkgHandling;
	std::string newPacket(bool reqReturn, std::string& addr, std::string& contents);
public:
	std::string receive(std::string& packet, size_t& outputSize); // Input from SQF
	void queue(LuaPackage* pkg); // Output from internal schedulers
};