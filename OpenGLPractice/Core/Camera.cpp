#include "Camera.h"

Camera::Camera()
{	
	this->field_of_view = 40;
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->position = glm::vec3{0.0f , 0.0f, 0.0f};
	this->projectionMatrix = glm::perspective(glm::radians(this->field_of_view), 2048.0f/1536.0f, 0.1f, 1000.0f);
}

Camera::~Camera()   
{

}

void Camera::UpdateProjectionMatrix(float fov) {
	this->field_of_view = fov;
	this->field_of_view = this->field_of_view < 1.0f ? 1.0f : this->field_of_view;
	this->field_of_view = this->field_of_view > 60.0f ? 60.0f : this->field_of_view;
	this->projectionMatrix = glm::perspective(glm::radians(this->field_of_view), 2048.0f / 1536.0f, 0.1f, 1000.0f);
}
