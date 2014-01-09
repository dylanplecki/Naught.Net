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

/* Packet Flags */

#define P_FLAG_NULL 0
#define P_FLAG_ERROR 1
#define P_FLAG_CONTINUE 2
#define P_FLAG_PROCESS_CODE 3
#define P_FLAG_NEW_SCHEDULER 4
#define P_FLAG_REQUEST_OUTPUT 5
#define P_FLAG_SEND_TO_INSTANCE 6

/* Packet Interface Definitions */

#define PACKET_LEN_RET 1
#define PACKET_LEN_ADR 16
#define PACKET_LEN_EXP 16

class IOHandler
{
private:
	static IOHandler *s_instance;
	std::vector<LuaScheduler*> schedulers;
	tbb::concurrent_queue<LuaPackage*> outputQueue;
	std::unordered_map<std::string,LuaPackage*> pkgHandling;
	std::string newPacket(int pFlag, std::string& addr, std::string& contents);
public:
	std::string receiveInput(const std::string& packet, size_t outputSize); // Input from SQF
	void queueOutput(LuaPackage* pkg); // Output from internal schedulers

	/* Singleton Function */
	static IOHandler *instance()
    {
        if (!s_instance)
			s_instance = new IOHandler;
        return s_instance;
    };
};