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
	float field_of_view;

public:
	glm::vec3 position;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	inline glm::mat4 getViewMatrix(){ 
		this->viewMatrix = glm::lookAt(this->position , this->position + this->cameraFront , this->cameraUp);
		return this->viewMatrix; 
	}
	inline glm::mat4 getProjectionMatrix() const { return this->projectionMatrix; }
	inline float Field_Of_View() const { return this->field_of_view; };

	void UpdateProjectionMatrix(float fov);

	Camera();
	~Camera();
};

