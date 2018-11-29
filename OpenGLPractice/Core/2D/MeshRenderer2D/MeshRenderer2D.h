#pragma once

#include <memory>
#include <glad/glad.h>
#include <iostream>
#include "../Mesh2D/Mesh2D.h"
#include "../../IEComponent.h"
#include "../../Material.h"

namespace AR {

	class MeshRenderer2D: public IEComponent
	{
	private:
		GLuint vertexBuffer;
		GLuint indexBuffer;

		GLuint vertexArrayObject;

		std::shared_ptr<AR::Material> material;

	public:
		std::shared_ptr<AR::Mesh2D> mesh2D;

		MeshRenderer2D() {};
		~MeshRenderer2D() {};

		void setMesh2D(std::shared_ptr<AR::Mesh2D>&&);

		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};

}
