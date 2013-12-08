/*
	Program: Naught.Net Dynamic Link Library (DLL)
	Author: Dylan Plecki <dylanplecki@gmail.com>
	License:
		Copyright (C) 2013 Dylan Plecki. All rights reserved.
		This work is licensed under the Microsoft Reference Source License (MS-RSL).
		Please reference the LICENSE.txt file included with this program for more information,
		Or visit <http://referencesource.microsoft.com/referencesourcelicense.aspx> for a copy.
*/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

/* Definitions */

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#define WORKER_IDLE_MIN 1 // Minimum number of idle workers.
#define WORKER_ALL_MAX 10 // Maximum number of active and idle workers.
#define WORKER_IDLE_TIMEOUT 300000 // Worker idle timeout in milliseconds, <= 0 for infinite.
#define WORKER_MAX_OPERATIONS 512 // Maximum number of operations a worker may perform before being destroyed (prevents memory leaks).

#define PKG_ACCESS_TIMEOUT 0 // Default package access mutex lock timeout in milliseconds, <= 0 for infinite.

#define RVE_INTERFACE_DELIM "~" // RVE parameter delimiter for communication.
#define RVE_OUTPUT_ERROR "NAUGHT_NET_ERROR" // Output error message.
#define RVE_OUTPUT_END "NAUGHT_NET___EOO" // End of output or return.
#define RVE_OUTPUT_NULL "NAUGHT_NET__NULL" // Return nothing/null.

/* Includes */

#include "version.h"

#include <windows.h>
//#include <Shlwapi.h>
#include <math.h>

//#include <iostream>
//#include <fstream>
#include <functional>
#include <chrono>
//#include <thread>
#include <atomic>
#include <future>
#include <string>
#include <vector>
#include <map>
//#include <regex>

#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>

#include "lua.hpp"

/*
#include <curl.h>

#include <pugixml.hpp>

//#include <yaml-cpp\yaml.h>

#include <hex.h>
#include <md2.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <shacal2.h>
*/

/*
#ifdef NDEBUG
	#pragma comment(lib,"cryptlib.lib")
	#pragma comment(lib,"libcurl_a.lib")
#else
	#pragma comment(lib,"cryptlibd.lib")
	#pragma comment(lib,"libcurl_a_debug.lib")
#endif

#pragma comment(lib,"libyaml-cppmd.lib")
*/