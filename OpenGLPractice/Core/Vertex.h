#pragma once

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

namespace ar {
	struct Vertex {
		glm::vec3 position;    //3
		glm::vec2 uv;		// 2
		glm::vec3 normal;      // 3

		Vertex(glm::vec3 position = glm::vec3(0.0f), glm::vec2 uv = glm::vec2(0.0f) , glm::vec3 normal = glm::vec3(0.0f)):position(position),uv(uv),normal(normal) {}
	};
}
