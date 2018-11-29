#include "MeshRenderer2D.h"

namespace AR {

	void MeshRenderer2D::setMesh2D(std::shared_ptr<AR::Mesh2D>&& mesh2D) {
		this->mesh2D = mesh2D;
	}

	void MeshRenderer2D::OnStart() {
		this->material = std::make_shared<AR::Material>(std::move(std::make_shared<AR::Shader>("./Shaders/2D/VertexShader2D.vs", "./Shaders/2D/FragmentShader2D.fs", 1)));
		
		//Preparing the Vertex Array Object
		glGenVertexArrays(1, &this->vertexArrayObject);
		glBindVertexArray(this->vertexArrayObject);

		//Preparing the Vertex Buffer
		glGenBuffers(1, &this->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->mesh2D->vertices), &this->mesh2D->vertices.front(), GL_STATIC_DRAW);

		//Preparing the Index Buffer
		glGenBuffers(1, &this->indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->mesh2D->indices), &this->mesh2D->indices.front(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 2, (void*)(0));

		glEnableVertexAttribArray(0);
	}

	void MeshRenderer2D::OnUpdate() {
		this->material->Shader()->bind();
		glBindVertexArray(this->vertexArrayObject);
		glEnableVertexAttribArray(0);
	
		glDrawElements(GL_TRIANGLES, this->mesh2D->indices.size(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glBindVertexArray(NULL);
		this->material->Shader()->unbind();
	}

	void MeshRenderer2D::OnDestroy() {
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glBindVertexArray(NULL);
		glDeleteBuffers(1, &this->vertexBuffer);
		glDeleteBuffers(1, &this->indexBuffer);
		glDeleteVertexArrays(1 , &this->vertexArrayObject);
	}
}

