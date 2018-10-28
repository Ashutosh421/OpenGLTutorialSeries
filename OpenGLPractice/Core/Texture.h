#pragma once

#include <glad/glad.h>
#include "../Utilities/TextureUtils.h"
#include <string>
#include <opencv2/opencv.hpp>

namespace AR {

	class Texture
	{
	private:
		GLuint textureID;
		bool isReady = false;
		GLuint textureUnit;

	public:
		void bind(GLuint textureUnit);
		void unbind();

		Texture(std::string, GLint imageFormat = GL_RGB);
		~Texture();
	};

}
