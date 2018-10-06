#include "FileUtils.h"

/*
Reading the content from file
*/
std::string FileUtils::ReadFileContent(const std::string& filePath) {
	std::ifstream fStream{filePath , std::fstream::in};   //Opening the file in Read Mode
	assert(fStream.is_open() && "Could not open file ");
	std::stringstream fContent;
	fContent << fStream.rdbuf();
	fStream.close();
	return fContent.str();
}