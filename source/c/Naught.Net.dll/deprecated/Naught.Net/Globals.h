/*
	This file is part of the Naught.Net DLL (Dynamic Link Library).

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Please reference the accompanying license file for complete
	legal information on the use, distribution, and reproduction
	of this code.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

// System Defines
#define WIN32_LEAN_AND_MEAN

// Program Defines
#define SOFTWARE_VERSION		"1.0.1.1"
#define CONFIG_FILE				"config.yml"

// Default Defines
#define FUNC_DELIMETER			"#"
#define PARAM_DELIMETER			"~"
#define RETURN_ERROR			"#!NAUGHT_NET_ERROR"
#define RETURN_TRUNCATED		"#!NAUGHT_NET_TRUNC"
#define RETURN_HANDLE			"#!NAUGHT_NET_HANDL"
#define RETURN_NULL				"#!NAUGHT_NET__NULL"
#define MAX_THREADS				10
#define THREAD_TIMEOUT			300					// Seconds
#define HTTP_CON_TIMEOUT		150					// Seconds
#define HTTP_MAX_CON_WRITE		1048576				// Bytes
#define HTTP_MAX_CON_DOWNLOAD	HTTP_MAX_CON_WRITE	// Bytes
#define HTTP_MAX_CON_UPLOAD		524288				// Bytes

// Platform Detection
#define PLATFORM_WINDOWS	1
#define PLATFORM_MAC		2
#define PLATFORM_UNIX		3
#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif

// Standard Header Files
#include "stdafx.h"

using namespace std;

extern bool Initialization;
extern int curOutputSize;

#endif