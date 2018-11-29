#pragma once
#include <string>
#include <vector>
#include "../../../Entity.h"
#include "../../Mesh2D/Mesh2D.h"
#include "../../MeshRenderer2D/MeshRenderer2D.h"
#include "../../Vertex2D/Vertex2f.h"

namespace AR {

	class Rectangle: public Entity
	{
	private:

	public:
		std::shared_ptr<AR::MeshRenderer2D> renderer2D;

		Rectangle(std::string&& , u_long id);
		~Rectangle();
	};

}

