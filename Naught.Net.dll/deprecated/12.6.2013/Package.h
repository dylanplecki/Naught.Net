#pragma once

class Package
{
private:
	std::timed_mutex pkgLock;
	// Consumable
	std::vector<std::string> contents;
	// Return
	bool readDone;
	std::string result;
	size_t resPos;
	// Functions
	bool authorize(int timeOut = PKG_ACCESS_TIMEOUT) {return this->pkgLock.try_lock_for(std::chrono::milliseconds(timeOut));};
	void deauthorize() {this->pkgLock.unlock();};
public:
	Package(std::vector<std::string>& args); // Constructor
	~Package(); // Deconstructor
	void seal() {this->pkgLock.lock();};
	// Getter Methods
	const std::vector<std::string>& getContents() {return this->contents;};
	// Reader [Scanner] Methods
	const std::string& readResult(size_t blockSize);
	// Setter Methods
	void setResult(std::string& newResult) {this->result = newResult;};
};