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


class Package
{
private:
	uint32_t handle;
	static uint32_t handleCounter;
	std::mutex lock;
	std::string instance;
	std::string contents;
	size_t outputCounter;
public:
	Package(std::string& instance, std::string& contents);
	~Package(void);
	std::string instance();
	std::string get();
	std::string& open();
	void close();
};