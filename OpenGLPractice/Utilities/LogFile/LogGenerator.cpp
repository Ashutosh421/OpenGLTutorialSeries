#include "LogGenerator.h"

namespace AR {

	std::stringstream LogGenerator::str;

	void LogGenerator::Log(const std::string& out) {
		LogGenerator::str << out << std::endl;
		std::cout << out << std::endl;
	}
}
