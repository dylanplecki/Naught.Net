#pragma once

#define THREAD_MIN 1 // Minumum number of threads (not used)
#define THREAD_MAX (concurrency::GetProcessorCount() * 4) // Maximum number of threads
#define THREAD_TIMEOUT (60 * 1000) // Thread idle timeout in milliseconds

class distributer
{
private:
	/* Containers */
	concurrency::concurrent_queue<package*> scheduler_queue; // Internal
	concurrency::concurrent_queue<package*> eshipping_queue; // External
	concurrency::concurrent_unordered_map<size_t, package*> processing_area;
	/* Non-Characteristic */
	static distributer *s_instance; // For singleton instance
	std::mutex queue_lock;
	std::condition_variable queue_idle;
	/* Functions */
	size_t getPacketId(std::string &packet);
	std::string fillText(std::string text, char fill, size_t len);
	void queueOut(package* pkg); // eshipping_queue
	void queueIn(package* pkg); // scheduler_queue
	package* decryptPacket(std::string &packet);
	std::string encryptPacket(std::string pFlags, size_t pID, std::string pAddr, std::string pContent);
	std::string encryptPacket(package* pkg, size_t size);
public:
	distributer();
	~distributer();
	/* Interaction Behaviors */
	package* request(); // Internal, return nullptr on fail/timeout
	void deliver(package* pkg); // Internal
	std::string deliver(std::string &pPacket); // External
	/* Worker Behaviors */
	void workerJoin(worker* wrkr);
	void workerDetach(worker* wrkr);
	/* Singleton Code */
	static distributer *instance()
	{
		if (!s_instance)
			s_instance = new distributer;
		return s_instance;
	};
};

distributer* distributer::s_instance = nullptr;