#pragma once

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

namespace AR {
	struct Vertex2f
	{
		glm::vec2 position;
		glm::vec2 uv;

		Vertex2f(glm::vec2 position = glm::vec2(0.0f) , glm::vec2 uv = glm::vec2(0.0f)):position(position),uv(uv){}
	};
}