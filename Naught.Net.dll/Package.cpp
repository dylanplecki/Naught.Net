/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

#include "stdafx.h"
#include "Package.h"


Package::Package(std::string& pAddress, std::string& pContents) : address(pAddress), contents(pContents) {};

Package::~Package(void) {};

std::string Package::getAddress()
{
	return this->address; // Won't change after class constructor, no need to protect
};

std::string Package::get(size_t& size)
{
	std::lock_guard<std::mutex>(this->lk);
	size_t start = this->outputCounter;
	this->outputCounter += size;
	return this->contents.substr(start, this->outputCounter);
};

bool Package::gotAll()
{
	return (this->outputCounter >= contents.size());
};

std::string& Package::open()
{
	this->lk.lock();
	return this->contents;
};

void Package::close()
{
	this->lk.unlock();
};