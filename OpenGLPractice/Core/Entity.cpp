#include "Entity.h"

namespace AR {
	Entity::Entity(const std::string& name, u_long id):name(name),id(id)
	{
		
	}

	Entity::~Entity()
	{
		for (auto &component : this->components) {
			component->OnDestroy();
			delete component;
		}
	}

	void Entity::AddChild(const Entity* child) {
		std::forward_list<const Entity*>::iterator it = std::find_if(this->children.begin(), this->children.end(), [&](const Entity* x)->bool{
			return x->ID() == child->ID();
		});
		if (it != this->children.end()) {
			this->children.emplace_front(child);
		}
	};

	void Entity::SetParent(Entity* parent) {
		this->parent = parent;
	}

	void Entity::OnUpdate() {
		std::cout << "On Entity Update" << std::endl;
	}
}


