#pragma once

#include <exception>

namespace AR {

	struct c_exception : public std::exception
	{
	private:
		const char* eMessage;
		unsigned int lineNo;
		const char* fileName;

	public:

		c_exception(const char* eMessage, unsigned int lineNo, const char* fileName) :eMessage(eMessage), lineNo(lineNo), fileName(fileName) {}

		const char* Message() const { return this->eMessage; }
		const unsigned int LineNo() const { return this->lineNo; }
		const char* FileName() const { return this->fileName; }
	};

}

