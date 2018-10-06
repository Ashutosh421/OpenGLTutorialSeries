#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utilities/Scale/Scale.h"

class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

public:
	glm::vec3 position;
	glm::vec3 cameraFront;

	inline glm::mat4 getViewMatrix(){ 
		this->viewMatrix = glm::lookAt(this->position , this->position + this->cameraFront , glm::vec3(0.0f , 1.0f , 0.0f));
		return this->viewMatrix; 
	}
	inline glm::mat4 getProjectionMatrix() const { return this->projectionMatrix; }

	Camera();
	~Camera();
};

