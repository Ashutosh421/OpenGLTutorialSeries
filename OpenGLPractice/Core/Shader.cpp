#include "Shader.h"

namespace AR {

	Shader::Shader(std::string vShaderPath, std::string fShaderPath, short verbose)
	{
		vShaderID = glCreateShader(GL_VERTEX_SHADER);
		fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vSource = FileUtils::ReadFileContent(vShaderPath);
		std::string fSource = FileUtils::ReadFileContent(fShaderPath);

		if (verbose == 2) std::cout << "Vertex Shader: " << std::endl << vSource << std::endl << "Fragment Shader: " << std::endl << fSource << std::endl;

		const GLchar* vSource_str = vSource.c_str();
		const GLchar* fSource_str = fSource.c_str();

		glShaderSource(vShaderID, 1, &vSource_str, NULL);
		glShaderSource(fShaderID, 1, &fSource_str, NULL);

		bool compileStatus = ShaderUtils::CompileShaders(vShaderID, fShaderID);
		if (compileStatus && verbose <= 2) std::cout << "Shaders successfully compiled" << std::endl;
		if (!compileStatus) return;

		//Create the Shader Program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vShaderID);
		glAttachShader(shaderProgram, fShaderID);

		bool linkStatus = ShaderUtils::LinkProgram(shaderProgram);
		if (linkStatus && verbose <= 2) std::cout << "Program successfully linked" << std::endl;
		if (!linkStatus) return;

		isReady = true;
		glDeleteShader(this->vShaderID); //Freeing up the Vertex Shader allocated buffer
		glDeleteShader(this->fShaderID); //Freeing up the Fragment Shader allocated buffer
	}

	void Shader::setInt(std::string uniformName, GLint value) {
		GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
		glUniform1i(uniformLocation, value);
	}

	void Shader::setFloat(std::string uniformName, GLfloat value) {
		GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
		glUniform1f(uniformLocation, value);
	}

	void Shader::setMat4(std::string uniformName, glm::mat4 mat) {
		GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
	}

	Shader::~Shader()
	{
		if (isReady) {
			glDeleteProgram(this->shaderProgram);
		}
	}

	void Shader::bind() {
		if (isReady) {
			glUseProgram(this->shaderProgram);
		}
	}

	void Shader::unbind() {
		if (isReady) {
			glUseProgram(NULL);
		}
	}

}

