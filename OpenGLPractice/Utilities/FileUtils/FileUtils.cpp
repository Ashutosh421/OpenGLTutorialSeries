#include "FileUtils.h"

namespace AR {


	/*
	Reading the content from file
	*/
	std::string FileUtils::ReadFileContent(const std::string& filePath) {
		std::ifstream fStream{ filePath , std::fstream::in };   //Opening the file in Read Mode
		assert(fStream.is_open() && "Could not open file ");
		std::stringstream fContent;
		fContent << fStream.rdbuf();
		fStream.close();
		return fContent.str();
	}

	void FileUtils::WriteToFile(const std::string& fileName, const std::string& fileContent) {
		std::ofstream fWStream{ fileName , std::fstream::out };
		fWStream << fileContent;
		fWStream.close();
	}
}
