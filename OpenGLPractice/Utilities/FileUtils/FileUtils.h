#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <assert.h>

class FileUtils
{
private:
	FileUtils() {};
	~FileUtils() {};

public:
	static std::string ReadFileContent(const std::string&);
};

