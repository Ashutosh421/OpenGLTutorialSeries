#pragma once

#include <string>
#include <exception>
#include <GLFW\glfw3.h>
#include <forward_list>
#include <memory>
#include <functional>

#include "CException.h"
#include "../Utilities/LogFile/LogGenerator.h"
#include "../EventManagement/IKeyEvent.h"
#include "GLFWKeyMap.h"

namespace AR {

	class window_exception : public AR::c_exception {
	public:
		window_exception(const char* eMessage, unsigned int lineNo, const char* fileName) :c_exception(eMessage, lineNo, fileName) {}
	};

	class Window
	{
	private:
		std::string windowName{ "Window" };
		unsigned int width{1024};
		unsigned int height{728};

		GLFWwindow* glfwWindow;
		std::forward_list<std::shared_ptr<IKeyEvent>> keyEventListeners;

	public:
		void EnableKeyEvents();
		Window(std::string windowName , unsigned int , unsigned int);
		void Update();
		Window();
		void RegisterKeyEventListener(std::shared_ptr<IKeyEvent>);

		~Window();
	};

}



