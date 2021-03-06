#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

#include "../Utilities/FileUtils/FileUtils.h"
#include "../Utilities/ShaderUtils/ShaderUtils.h"

class Shader
{
private:
	GLuint vShaderID;
	GLuint fShaderID;
	bool isReady = false;

public:
	void bind();
	void unbind();

	void setInt(std::string , GLint);
	void setFloat(std::string, GLfloat);
	void setMat4(std::string, glm::mat4);

	GLuint shaderProgram;


	Shader(std::string vShaderPath = "VertexShader.fs", std::string fShaderPath = "FragmentShader.fs", short verbose = 0);
	~Shader();
};

