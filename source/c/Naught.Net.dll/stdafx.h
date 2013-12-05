// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "version.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
//#include <Shlwapi.h>
#include <math.h>

//#include <iostream>
//#include <fstream>
#include <functional>
#include <chrono>
//#include <thread>
//#include <atomic>
#include <future>
#include <string>
#include <vector>
//#include <regex>

#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>

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