#include "Material.h"

namespace AR {

	Material::Material(std::shared_ptr<AR::Shader> shader):shader(shader)
	{
		
	}

	Material::~Material()
	{
	}
}

