#pragma once
#include <GLFW\glfw3.h>
#include "GLFWKeyMap.h"
#include "Window.h"

namespace AR {

	class InputManager
	{
	private:
		InputManager() {};
		~InputManager() {};
		static std::shared_ptr<AR::Window> currentWindow;

	public:
		static void SetCurrentWindow(std::shared_ptr<AR::Window>);
		static bool IsKeyDown(AR::KeyType);
		static bool IsKeyUp(AR::KeyType);
		static bool IsKeyRepeat(AR::KeyType);
	};

}

