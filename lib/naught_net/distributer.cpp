#include "stdafx.h"
#include "package.h"
#include "worker.h"
#include "distributer.h"


size_t getPacketId(std::string &packet)
{
	return boost::lexical_cast<size_t>(packet.substr(5, 5));
};


std::string distributer::fillText(std::string text, char fill, size_t len)
{
	std::string text_fill;
	while (text.size() < len)
	{
		text_fill += fill;
		--len;
	};
	return (text_fill + text);
};


void distributer::queueOut(package* pkg)
{
	eshipping_queue.push(pkg);
};


void distributer::queueIn(package* pkg)
{
	scheduler_queue.push(pkg);
	queue_idle.notify_one();
};


package* distributer::decryptPacket(std::string &packet)
{
	return new package(packet);
};


std::string distributer::encryptPacket(std::string pFlags, size_t pID, std::string pAddr, std::string pContent)
{
	return (fillText(pFlags, '0', 16) + fillText(std::to_string(pID), '0', 5) + fillText(pAddr, ' ', 32) + pContent);
};


std::string distributer::encryptPacket(package* pkg, size_t size)
{
	std::string content;
	bool delPkg = pkg->getContent(content, (size - PACKET_CONT_START));
	std::string ret = encryptPacket(pkg->getFlags(), pkg->getId(), pkg->getAddress(), content);
	if (delPkg)
	{
		delete pkg;
	};
	return ret;
};


distributer::distributer()
{
	// Empty
};


distributer::~distributer()
{
	// Empty
};

package* distributer::request() // Return nullptr on fail/timeout
{
	package* ret = nullptr;
	if (!scheduler_queue.try_pop(ret))
	{
		std::unique_lock<std::mutex> lk(queue_lock);
		queue_idle.wait_for(lk, std::chrono::milliseconds(THREAD_TIMEOUT), [this, &ret](){
			return scheduler_queue.try_pop(ret);
		});
	};
	return ret;
};


void distributer::deliver(package* pkg) // Output to RVE
{
	eshipping_queue.push(pkg);
};


std::string distributer::deliver(std::string &packet) // Input from RVE
{
	package* pkg = decryptPacket(packet);
	if (pkg->getId() == 0) // Get new Package
	{

	}
	else
	{
		if (processing_area.count(pkg->getId())) // Get multi-part package
		{

		}
		else
		{

		};
	};
};


void distributer::workerJoin(worker* wrkr)
{
	wrkr->getThread()->join();
	delete wrkr;
};


void distributer::workerDetach(worker* wrkr)
{
	wrkr->getThread()->detach();
	delete wrkr;
};