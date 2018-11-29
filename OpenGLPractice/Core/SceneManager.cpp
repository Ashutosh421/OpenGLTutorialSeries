#include <glad\glad.h>
#include "SceneManager.h"

namespace AR {

	std::unordered_map<std::string, std::shared_ptr<AR::Scene>> SceneManager::scenes;
	std::shared_ptr<AR::Scene> SceneManager::currentScene;

	void SceneManager::LoadScene(const std::string& sceneName) {
		auto it = AR::SceneManager::scenes.find(sceneName);
		if (it != AR::SceneManager::scenes.end()) {
			SceneManager::currentScene = it->second;
		}
	}

	void SceneManager::AddScene(std::shared_ptr<AR::Scene>&& newScene) {
		if (AR::SceneManager::scenes.find(newScene->Name()) == AR::SceneManager::scenes.end()) {
			AR::SceneManager::scenes.insert({newScene->Name() , newScene});
		}
	}

	void SceneManager::Update() {
		if (AR::SceneManager::currentScene) {
			glClearColor(AR::SceneManager::currentScene->backgroudColor.r, AR::SceneManager::currentScene->backgroudColor.b, AR::SceneManager::currentScene->backgroudColor.g, AR::SceneManager::currentScene->backgroudColor.a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			AR::SceneManager::currentScene->Update();
		}
	}
}


