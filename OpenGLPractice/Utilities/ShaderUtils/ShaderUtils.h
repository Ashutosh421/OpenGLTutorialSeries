#pragma once
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../FileUtils/FileUtils.h"

class ShaderUtils
{
private:
	ShaderUtils();

public:
	static bool CompileShaders(const GLuint& vShaderID, const GLuint& fShaderID);
	static bool LinkProgram(const GLuint& programID);

	~ShaderUtils();
};

