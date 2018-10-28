#pragma once

#include <sstream>
#include <iostream>

#include "../FileUtils/FileUtils.h"

namespace AR {
	struct LogGenerator
	{
	private:
		static std::stringstream str;

	public:
		static void Log(const std::string&);
	};
}

