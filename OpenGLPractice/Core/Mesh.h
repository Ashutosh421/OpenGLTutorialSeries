#pragma once
#include "IECompoent.h"
#include <glm\vec3.hpp>
#include <vector>
#include <iostream>

#include "Vertex.h"

namespace AR {

	class Mesh
	{
	public:
		std::vector<AR::Vertex> vertices;

		Mesh();
		~Mesh();
	};
}

