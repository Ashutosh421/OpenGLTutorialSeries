#include "InputManager.h"

namespace AR {

	std::shared_ptr<AR::Window> InputManager::currentWindow;

	void InputManager::SetCurrentWindow(std::shared_ptr<AR::Window> cWindow) {
		InputManager::currentWindow = cWindow;
	}

	bool InputManager::IsKeyDown(AR::KeyType kType) {
		int state = glfwGetKey(InputManager::currentWindow->Raw(), static_cast<int>(kType));
		return state == GLFW_PRESS;
	}

	bool InputManager::IsKeyRepeat(AR::KeyType kType) {
		int state = glfwGetKey(InputManager::currentWindow->Raw(), static_cast<int>(kType));
		return state == GLFW_REPEAT;
	}

	bool InputManager::IsKeyUp(AR::KeyType kType) {
		int state = glfwGetKey(InputManager::currentWindow->Raw(), static_cast<int>(kType));
		return state == GLFW_RELEASE;
	}

}
