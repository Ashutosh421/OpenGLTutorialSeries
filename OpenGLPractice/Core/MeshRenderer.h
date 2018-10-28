#pragma once

#include "IECompoent.h"
#include "Mesh.h"
#include <algorithm>

namespace AR {

	class MeshRenderer: public IEComponent
	{
	private: 
		std::shared_ptr<AR::Mesh> mesh;

	public:
		MeshRenderer() {};
		~MeshRenderer() {};

		void SetMesh(std::shared_ptr<AR::Mesh> mesh);
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};

}

