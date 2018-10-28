#include "Application.h"

namespace AR {

	Application* Application::instance = nullptr;

	Application* Application::Instance() {
		if (Application::instance == nullptr) {
			Application::instance = new Application();
		}
		return Application::instance;
	}

	bool Application::Init() {
		try {
			if (glfwInit() == GLFW_FALSE) {
				throw application_exception("GLFW Initialization Error", 15, "Application.cpp");
			}
			AR::LogGenerator::Log("GLFW Successfully Initialized");
			this->window = std::make_shared<AR::Window>("Window_1", 1024, 768);
			this->isRunning = true;
			return true;
		}
		catch (application_exception e) {
			std::stringstream se;
			se << e.Message() << " " << e.LineNo() << " " << e.FileName();
			LogGenerator::Log(se.str());
			return false;
		}
		catch (window_exception e) {
			std::stringstream se;
			se << e.Message() << " " << e.LineNo() << " " << e.FileName();
			LogGenerator::Log(se.str());
			return false;
		}
	}

	void Application::Stop() {
		this->isRunning = false;
	}

	void Application::Update() {
		this->window->Update();
	}
}
