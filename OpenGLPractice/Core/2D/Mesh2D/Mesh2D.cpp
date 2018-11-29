#include "Mesh2D.h"

namespace AR {

	Mesh2D::Mesh2D(std::vector<glm::vec2>&& vertices, std::vector<GLuint>&& indices)
	{	
		this->vertices = vertices;
		this->indices = indices;
	}


	Mesh2D::~Mesh2D()
	{
		this->vertices.clear();
		this->indices.clear();
	}
}

