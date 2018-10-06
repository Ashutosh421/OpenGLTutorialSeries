#pragma once

#include <glad/glad.h>
#include "../../Math/Vector2f.h"

struct Scale
{
private:
	Scale() = delete;
	~Scale() = delete;

public:
	static Vector2f size;
	void static setViewPort(GLuint, GLuint, GLuint, GLuint);
	Vector2f static NormalizedScreenCordinates(Vector2f);
};

