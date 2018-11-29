#pragma once
#include "IEComponent.h"
#include <glm\vec3.hpp>
#include <vector>
#include <iostream>

#include "Vertex3f.h"

namespace AR {

	class Mesh
	{
	public:
		std::vector<AR::Vertex3f> vertices;

		Mesh();
		~Mesh();
	};
}

