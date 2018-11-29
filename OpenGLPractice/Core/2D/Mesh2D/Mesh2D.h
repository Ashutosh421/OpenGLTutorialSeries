#pragma once
#include <vector>
#include <glad\glad.h>
#include "../Vertex2D/Vertex2f.h"
#include <glm\vec2.hpp>

namespace AR {

	class Mesh2D
	{
	public:
		//std::vector<AR::Vertex2f> vertices;
		std::vector<glm::vec2> vertices;
		std::vector<GLuint> indices;

		Mesh2D() {};
		Mesh2D(std::vector<glm::vec2>&& , std::vector<GLuint>&& indices);
		~Mesh2D();
	};

}

