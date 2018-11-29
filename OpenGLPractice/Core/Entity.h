#pragma once
#include <forward_list>
#include <string>
#include <algorithm>

#include "TypeDefs.h"
#include "SObject.h"
#include "IEComponent.h"
#include "Mesh.h"


namespace AR {
	class Entity: public SObject
	{
	private:
		std::forward_list<const Entity*> children;
		std::string name{"Entity"};
		const u_long id;
		Entity* parent;
		std::forward_list<std::shared_ptr<AR::IEComponent>> components;

	public:
		Entity(std::string&& name, u_long id);

		void AddChild(const Entity*);
		void SetParent(Entity*);

		void OnUpdate() override;
		void OnStart() override;
		void OnDestroy() override;

		template <typename T, typename = std::enable_if<std::is_base_of<IEComponent , T>::value>>
		void AddComponent() {
			std::shared_ptr<AR::IEComponent> com = std::make_shared<T>();
			this->components.push_front(std::make_shared<T>());
		}

		template <typename T, typename = std::enable_if<std::is_base_of<IEComponent, T>::value>>
		std::shared_ptr<AR::IEComponent> GetComponent() {
			for (auto &x : this->components) {
				if (std::dynamic_pointer_cast<T>(x)) {
					return x;
				}
			}
			return nullptr;
		}

		inline const std::forward_list<const Entity*>& Children() const { return this->children; };
		inline const int ID() const { return this->id; };
		inline const std::string Name() const { return this->name; }

		~Entity() {}
	};
}



