#pragma once
#include <string>
#include <unordered_map>
#include "Entity.h"
#include "..\Math\Color4f.h"

namespace AR {
	class Scene
	{
	private:
		std::string sceneName;
		std::unordered_map<std::string, std::shared_ptr<AR::Entity>> entities;

	public:
		AR::Color4f backgroudColor = Color4f(0, 0, 0, 0);
		explicit Scene(const std::string&&);
		~Scene();

		void Update();
		void AddChild(const std::shared_ptr<AR::Entity>&& entity);
		void RemoveChild();

		inline std::string Name() const { return this->sceneName; }
	};
}



