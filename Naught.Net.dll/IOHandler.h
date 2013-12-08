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

class Scheduler;
class Package;

class IOHandler
{
private:
	std::map<std::string,Scheduler*> instances;
	Queue<Package*> outputQueue;
	Scheduler* getInstance(std::string& name);
	void deleteInstance(std::string& name);
public:
	std::string input(Package* pkg);
	void output(Package* pkg);
};