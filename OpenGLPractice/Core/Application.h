#pragma once
#include <algorithm>
#include <memory>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <exception>
#include <string>

#include "Window.h"
#include "CException.h"
#include "../Utilities/LogFile/LogGenerator.h"
#include <sstream>

namespace AR {

	struct application_exception : public AR::c_exception
	{
		application_exception(const char* eMessage, unsigned int lineNo, const char* fileName) :c_exception(eMessage, lineNo, fileName) {}
	};


	class Application
	{
	private:
		static Application* instance;
		std::shared_ptr<AR::Window> window;

		Application(){}
		~Application(){}

		bool isRunning = false;

	public:
		bool Init();
		void Stop();
		void Update();

		static Application* Instance();

		inline bool IsRunning() const { return this->isRunning; }
		inline std::shared_ptr<AR::Window> Window() const { return this->window; }
	};

}
