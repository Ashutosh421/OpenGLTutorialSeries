#include "Texture.h"

Texture::Texture(std::string texturePath, GLint imageFormat)
{
	glGenTextures(1, &textureID);
	const cv::Mat imageData = TextureUtils::LoadImageFromPath(texturePath);
//	cv::imshow("Loaded Texture", imageData);
	cv::flip(imageData, imageData, 0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint targetFormat = imageFormat == GL_RGB ? GL_BGR : GL_BGRA;
	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, imageData.rows, imageData.cols, 0, targetFormat, GL_UNSIGNED_BYTE, (void*)imageData.data);
	glBindTexture(GL_TEXTURE_2D, NULL);
	isReady = true;
}

void Texture::bind(GLuint textureUnit) {
	if (isReady) {
		this->textureUnit = textureUnit;
		glActiveTexture(GL_TEXTURE0 + this->textureUnit);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}

void Texture::unbind() {
	if (isReady) {
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}
