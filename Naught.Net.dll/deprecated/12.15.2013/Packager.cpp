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
#include "Packager.h"


Package* Packager::pack(std::string& input)
{
	
	std::string pAddress = "";
	std::string pContents = "";
	return new Package(pAddress, pContents);
};

std::string Packager::unpack(Package* pkg)
{

};

std::string Packager::send(std::string& input)
{

};