#include "IOManager.h"
#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	// Open the file that we want to read and specify that we want to read in binary
	std::ifstream file(filePath, std::ios::binary);

	// Check if the file opened correctly
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	// seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	// Reading the file
	file.read((char*)&buffer[0], fileSize);

	return true;
}