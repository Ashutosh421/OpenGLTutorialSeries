#pragma once
#include <unordered_map>
#include <string>

#include "Window.h"
#include "Scene.h"

namespace AR {
	class SceneManager
	{
	public:
		static void LoadScene(const std::string&);
		static void AddScene(std::shared_ptr<AR::Scene>&&);
		static void Update();
		static std::shared_ptr<AR::Scene> currentScene;

	private:
		static std::unordered_map<std::string, std::shared_ptr<AR::Scene>> scenes;

		SceneManager() {};
		~SceneManager() {};
	};
}



