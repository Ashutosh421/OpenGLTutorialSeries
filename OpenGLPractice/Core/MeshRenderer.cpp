#include "MeshRenderer.h"

namespace AR {

	void MeshRenderer::SetMesh(std::shared_ptr<AR::Mesh> mesh) {
		this->mesh = mesh;
	}

	void MeshRenderer::OnStart() {
		std::cout << "Mesh Renderer On Start";
	}

	void MeshRenderer::OnUpdate() {
		if (this->mesh) {
			std::cout << "Mesh Renderer On Update";
		}
	}

	void MeshRenderer::OnDestroy() {
		std::cout << "Mesh Renderer On Destroy";
	}
}


