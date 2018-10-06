#include "ShaderUtils.h"

bool ShaderUtils::CompileShaders(const GLuint& vShaderID, const GLuint& fShaderID) {
	glCompileShader(vShaderID);
	glCompileShader(fShaderID);

	auto getShaderCompileStatus = [](std::string shaderType, GLuint shaderID)->bool {
		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			std::cerr << "Compilation Failed " << shaderType << std::endl;
			GLint logInfoLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logInfoLength);

			std::vector<GLchar> errorLog(logInfoLength);
			glGetShaderInfoLog(shaderID, logInfoLength, &logInfoLength, &errorLog[0]);

			for (GLchar& error: errorLog) {
				std::cout << error;
			}
			std::cout << std::endl;

			glDeleteShader(shaderID);
		}
		return isCompiled == GL_TRUE;
	};

	return getShaderCompileStatus("Vertex Shader", vShaderID) && getShaderCompileStatus("Fragment Shader" , fShaderID);
}

bool ShaderUtils::LinkProgram(const GLuint& programID) {
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		std::cerr << "Program Linking failed" << std::endl;
		//Get Log Info Lenth
		GLint logInfoLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logInfoLength);

		//Getting the info Log
		std::vector<GLchar> errorLog(logInfoLength);
		glGetProgramInfoLog(programID, logInfoLength, &logInfoLength, &errorLog[0]);

		for (GLchar error: errorLog) {
			std::cout << error;
		}
		std::cout << std::endl;
		glDeleteProgram(programID);
	}
	return isLinked == GL_TRUE;
}

ShaderUtils::~ShaderUtils()
{
}




