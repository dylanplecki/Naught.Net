/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#pragma once

#include "targetver.h"

#include <windows.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <future>
#include <string>
#include <vector>
#include <regex>
#include <boost\lexical_cast.hpp>
#include <curl.h>
#include <hex.h>

#include <md2.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <shacal2.h>

#ifdef NDEBUG
	#pragma comment(lib,"cryptlib.lib")
	#pragma comment(lib,"libcurl_a.lib")
#else
	#pragma comment(lib,"cryptlibd.lib")
	#pragma comment(lib,"libcurl_a_debug.lib")
#endif