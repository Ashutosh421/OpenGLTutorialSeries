#pragma once
#include <string>
#include <unordered_map>
#include "Entity.h"

namespace AR {
	class Scene
	{
	private:
		std::string sceneName;
		std::unordered_map<std::string, std::shared_ptr<AR::Entity>> entities;

	public:
		explicit Scene(const std::string&&);
		~Scene();

		void Update();
		void AddChild(const std::shared_ptr<AR::Entity>&& entity);
		void RemoveChild();

		inline std::string Name() const { return this->sceneName; }
	};
}



