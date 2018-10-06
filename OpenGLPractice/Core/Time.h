#pragma once
#include <GLFW\glfw3.h>

class Time
{
private:
	Time();
	~Time();
	static float prevTime;

public:
	static float deltaTime;
	static float time;

	static void Update();
};

