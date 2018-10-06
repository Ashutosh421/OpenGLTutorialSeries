#include "Camera.h"

Camera::Camera()
{	
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->position = glm::vec3{0.0f , 0.0f, 0.0f};
	this->projectionMatrix = glm::perspective(glm::radians(40.0f), 2048.0f/1536.0f, 0.1f, 1000.0f);
}

Camera::~Camera()   
{

}
