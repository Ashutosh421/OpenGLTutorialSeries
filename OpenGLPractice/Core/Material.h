#pragma once

#include "Shader.h"
#include "Texture.h"
#include <forward_list>

namespace AR {

	class Material
	{
	private:
		std::shared_ptr<AR::Shader> shader;
		std::forward_list<AR::Texture> textures;

	public:
		Material(std::shared_ptr<AR::Shader>&&);
		~Material();

		inline const std::shared_ptr<AR::Shader>& Shader() const { return this->shader; }
		inline const std::forward_list<AR::Texture>& Textures() const { return this->textures; }
	};

}

