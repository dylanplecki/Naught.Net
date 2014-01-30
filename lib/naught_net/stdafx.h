// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concrtrm.h>

// STD Header Files:
#include <bitset>
#include <vector>
#include <string>
#include <hash_map>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <unordered_map>

// Boost Header Files:
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>