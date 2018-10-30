#pragma once
#include <forward_list>
#include <string>
#include <algorithm>

#include "SObject.h"
#include "IECompoent.h"
#include "Mesh.h"

typedef unsigned long long int u_long;

namespace AR {
	class Entity: public SObject
	{
	private:
		std::forward_list<const Entity*> children;
		std::string name{"Entity"};
		const u_long id;
		Entity* parent;
		std::forward_list<AR::IEComponent*> components;

	public:
		Entity(const std::string& name, u_long id);

		void AddChild(const Entity*);
		void SetParent(Entity*);
		void OnUpdate() override;

		template <typename T, typename = std::enable_if<std::is_base_of<IEComponent , T>::value>>
		void AddComponent() {
			IEComponent* com = new T();
			this->components.push_front(com);
			com->OnStart();
		}

		inline const std::forward_list<const Entity*>& Children() const { return this->children; };
		inline const int ID() const { return this->id; };
		inline const std::string Name() const { return this->name; }

		~Entity();
	};
}



