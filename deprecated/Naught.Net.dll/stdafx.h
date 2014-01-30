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

/* Includes */

#include "version.h"

#include <windows.h>
//#include <Shlwapi.h>
#include <math.h>

//#include <iostream>
//#include <fstream>
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>
#include <string>
#include <vector>
//#include <map>
#include <unordered_map>
//#include <queue>
//#include <regex>

//#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>
//#include <boost\tokenizer.hpp>

#include "lua.hpp"

#include "tbb\concurrent_queue.h"
#include "tbb\concurrent_hash_map.h"
#include "tbb\enumerable_thread_specific.h"

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

#pragma comment(lib,"tbb.lib")
#pragma comment(lib,"liblua-static.lib")
#pragma comment(lib,"luac-static.lib")