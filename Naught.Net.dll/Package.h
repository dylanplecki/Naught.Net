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
	std::mutex lk;
	std::string address; // Unique value
	std::string contents;
	size_t outputCounter;
public:
	Package(std::string& pAddress, std::string& pContents);
	~Package(void);
	std::string getAddress();
	std::string get(size_t& size);
	bool gotAll();
	std::string& open();
	void close();
};