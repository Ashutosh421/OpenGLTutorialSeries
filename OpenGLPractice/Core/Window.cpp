#include "Window.h"

namespace AR {

	Window::Window() :Window(static_cast<std::string>("Window"), static_cast<unsigned int>(1024), static_cast<unsigned int>(768)) {}

	Window::Window(std::string windowName , unsigned int width , unsigned int height):windowName(windowName),width(width),height(height)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->glfwWindow = glfwCreateWindow(this->width, this->height, this->windowName.c_str(), nullptr, nullptr);
		if (this->glfwWindow == nullptr) {
			throw window_exception("Couldn't create GLFW Window" , 15 , "Window.cpp");
		}
		LogGenerator::Log("Successfully Created Window");
		glfwMakeContextCurrent(this->glfwWindow);
		LogGenerator::Log("Successfully Created OpenGL Context");
	}

	void Window::Update() {
		glfwSwapBuffers(this->glfwWindow);
		glfwPollEvents();
	}
	 
	Window::~Window()
	{
		glfwDestroyWindow(this->glfwWindow);
	}
}

