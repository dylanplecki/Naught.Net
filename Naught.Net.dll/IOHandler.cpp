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
#include "Queue.h"
#include "Scheduler.h"
#include "IOHandler.h"

std::string IOHandler::newPacket(bool reqReturn, std::string& addr, std::string& contents)
{
	char expectReturn;
	if (reqReturn) {expectReturn = '1';} else {expectReturn = '0';};
	return (expectReturn + addr + contents);
};

std::string IOHandler::receive(std::string& packet, size_t& outputSize) // Called from SQF
{
	std::lock_guard<std::mutex> lk(this->extIO); // Only 1 IO handler instance may run at a time
	bool expectReturn = false;
	std::string packetContent = INTERFACE_RET_NULL;
	bool returnPacket = boost::lexical_cast<bool,std::string>(packet.substr(0, PACKET_LEN_RET));
	std::string targetAddress = packet.substr(PACKET_LEN_RET, PACKET_LEN_ADR);
	if (returnPacket) // Return scheduled output
	{
		Package* pkg = nullptr;
		if (targetAddress == ADDRESS_GET_NEW)
		{
			if (this->outputQueue.size() > 0)
			{
				pkg = this->outputQueue.next();
				targetAddress = pkg->getAddress();
				pkgHandling[targetAddress] = pkg;
			};
		}
		else // Find packet in current handling stack
		{
			if (this->pkgHandling.count(targetAddress))
			{
				pkg = pkgHandling[targetAddress];
			};
		};
		if (pkg != nullptr)
		{
			packetContent = pkg->get(outputSize);
			if (pkg->gotAll()) // Then remove all pkg instances
			{
				pkgHandling.erase(targetAddress);
				delete pkg;
			} else {expectReturn = true;};
		};
	}
	else // Send to scheduler
	{
		if (schedulers.size() > 0)
		{
			Scheduler* sched = schedulers.back();
			Package* pkg = new Package(targetAddress, packet.substr((PACKET_LEN_RET + PACKET_LEN_ADR), std::string::npos));
			for (auto &scheduler : this->schedulers)
			{
				if (scheduler->search(targetAddress)) // Send to thread
				{
					sched = scheduler;
					break;
				};
			};
			sched->send(pkg);
		} else {packetContent = ERRORMSG("No scheduler found.");};
	};
	return this->newPacket(expectReturn, targetAddress, packetContent);
};

void IOHandler::queue(Package* pkg) // Called from internal threaded workers
{
	this->outputQueue.add(pkg);
};