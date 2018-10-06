#include "Time.h"

float Time::deltaTime{ 0 };
float Time::prevTime{ 0 };
float Time::time{ 0 };

void Time::Update() {
	Time::time = glfwGetTime();
	Time::deltaTime = time - prevTime;
	prevTime = Time::time;
}