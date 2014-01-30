#pragma once

#define PACKET_FLAG_LEN 16
#define PACKET_IDEN_LEN 5
#define PACKET_ADDR_LEN 32
#define PACKET_CONT_LEN std::string::npos

#define PACKET_FLAG_START 0
#define PACKET_IDEN_START (PACKET_FLAG_START + PACKET_FLAG_LEN)
#define PACKET_ADDR_START (PACKET_IDEN_START + PACKET_IDEN_LEN)
#define PACKET_CONT_START (PACKET_ADDR_START + PACKET_ADDR_LEN)

class packet
{
protected:
	/* States */
	size_t id;
	std::bitset<16> flags;
	std::string address; // Function name
	std::string content; // Arguments/return
public:
	/* Flag Behaviors */
	std::string getFlags();
	void setFlag(size_t pFlag, bool pSwitch = true);
	bool checkFlag(size_t flag);
	void resetFlags();
	/* Getter Behaviors */
	size_t getId();
	std::string getAddress();
	std::string getContent();
	/* Setter Behaviors */
	void setAddress(std::string &pAddr);
	void setContent(std::string pContent);
};