#include "Scene.h"

namespace AR {
	Scene::Scene(const std::string&& sceneName):sceneName(sceneName){}

	void Scene::Update() {
		for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
			it->second->OnUpdate();
		}
	}

	void Scene::AddChild(const std::shared_ptr<AR::Entity>&& entity) {
		auto it = this->entities.find(entity->Name());
		if (it == this->entities.end()) {
			this->entities.insert({ entity->Name() , entity });
			entity->OnStart();
		}
	}

	Scene::~Scene()
	{
		this->entities.clear();
	}
}


