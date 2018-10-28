#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <assert.h>

namespace AR {

	class FileUtils
	{
	private:
		FileUtils() {};
		~FileUtils() {};

	public:
		static std::string ReadFileContent(const std::string&);
		static void WriteToFile(const std::string&, const std::string&);
	};

}
