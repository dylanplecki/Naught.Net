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

class Package;
class Scheduler;

class Worker
{
private:
	std::mutex idle;
	std::condition_variable queued;
	void process();
public:
	Worker(Package* pkg);
	~Worker(void);
	void notify();
};