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
#include "LuaPackage.h"
#include "LuaScheduler.h"
#include "IOHandler.h"


IOHandler *IOHandler::s_instance = 0;

std::string IOHandler::newPacket(int pFlag, std::string& addr, std::string& contents)
{
	return (boost::lexical_cast<std::string,int>(pFlag) + addr + contents);
};

std::string IOHandler::receiveInput(const std::string& packet, size_t outputSize) // Called from SQF
{
	int packetFlag = boost::lexical_cast<int,std::string>(packet.substr(0, PACKET_LEN_RET));
	std::string targetIdentity = packet.substr(PACKET_LEN_RET, PACKET_LEN_ADR);
	std::string packetContent = packet.substr((PACKET_LEN_RET + PACKET_LEN_ADR), std::string::npos);

	int newPacketFlag = P_FLAG_NULL;
	std::string newPacketIdentity = targetIdentity;
	std::string newPacketContent;

	LuaPackage* pkg = nullptr;

	switch(packetFlag)
	{
	case P_FLAG_PROCESS_CODE:
		if (schedulers.size() > 0)
		{
			schedulers.back()->queuePackage(new LuaPackage(targetIdentity, packetContent));
		}
		else
		{
			newPacketFlag = P_FLAG_ERROR;
			newPacketContent = "No schedulers available for new instance.";
		};
		break;
	case P_FLAG_NEW_SCHEDULER:
		delete schedulers.front();
		schedulers.push_back(new LuaScheduler());
		break;
	case P_FLAG_REQUEST_OUTPUT:
		if (pkgHandling.count(targetIdentity))
		{
			pkg = pkgHandling[targetIdentity];
		}
		else
		{
			if (outputQueue.try_pop(pkg))
			{
				newPacketIdentity = pkg->getIdentity();
			};
		};
		if (pkg != nullptr)
		{
			newPacketContent = pkg->take(outputSize);
			if (pkg->isEmpty())
			{
				switch (pkg->getFlag())
				{
				case PKG_FLAG_ERROR:
					newPacketFlag = P_FLAG_ERROR;
					break;
				case PKG_FLAG_CODE:
					newPacketFlag = P_FLAG_PROCESS_CODE;
					break;
				};
				delete pkg;
			} else {newPacketFlag = P_FLAG_CONTINUE;};
		};
		break;
	case P_FLAG_SEND_TO_INSTANCE:
		bool found = false;
		for (auto scheduler : schedulers)
		{
			if (scheduler->search(targetIdentity, packetContent))
			{
				found = true;
				break;
			};
		};
		if (!found)
		{
			newPacketFlag = P_FLAG_ERROR;
			newPacketContent = "No matching instance found in current schedulers.";
		};
		break;
	};

	return newPacket(newPacketFlag, newPacketIdentity, newPacketContent);
};

void IOHandler::queueOutput(LuaPackage* pkg) // Called from internal scheduler
{
	outputQueue.push(pkg);
};