#include "Rectangle.h"

namespace AR {

	Rectangle::Rectangle(std::string&& name, u_long id) :Entity(static_cast<std::string&&>(name), id)
	{
		/*std::vector<AR::Vertex2f> vertices;
		vertices.push_back(AR::Vertex2f(glm::vec2(-1.0f, 1.0f)));
		vertices.push_back(AR::Vertex2f(glm::vec2(-1.0f, -1.0f)));
		vertices.push_back(AR::Vertex2f(glm::vec2(1.0f, -1.0f)));
		vertices.push_back(AR::Vertex2f(glm::vec2(1.0f, 1.0f)));*/

		std::vector<glm::vec2> vertices;
		vertices.push_back(glm::vec2(0.5f, 0.5f));
		vertices.push_back(glm::vec2(0.5f, -0.5f));
		vertices.push_back(glm::vec2(-0.5f, -0.5f));
		vertices.push_back(glm::vec2(-0.5f, 0.5f));

		std::vector<GLuint> indices = { 0, 1, 3,   // first triangle
									   1, 2, 3 };

		this->AddComponent<MeshRenderer2D>();

		std::shared_ptr<AR::MeshRenderer2D> renderer = std::dynamic_pointer_cast<AR::MeshRenderer2D>(this->GetComponent<AR::MeshRenderer2D>());
		renderer->setMesh2D(std::move(std::make_shared<AR::Mesh2D>(std::move(vertices) , std::move(indices))));
	}

	Rectangle::~Rectangle()
	{
	}

}

