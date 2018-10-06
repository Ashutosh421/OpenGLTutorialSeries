#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "../Core/Shader.h"
#include "../Math/Vector2f.h"
//#include "Core/Vertex/Vertex.h"
#include "../Utilities/Scale/Scale.h"
#include "../Core/Texture.h"
#include <opencv2/opencv.hpp>

Shader* s1;
Texture* t1;
Texture* t2;
Vector2f mouseScreenCordinates;

GLfloat textureBlendThreshold = 0.5f;

GLFWwindow* mainWindow;
int InitGLFW(short);
void InitGameData();
void GameLoop(short);
void ProcessInput(short);
void ShutDown(short);
void ErrorChecking();

//GLFWCallbacks
void On_GLFW_Window_Resize(GLFWwindow*, int, int);
void On_GLFW_CursorPositionMove(GLFWwindow*, double, double);
void On_GLFW_Key_Pressed(GLFWwindow*, int, int, int, int);

GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
};

GLubyte indices[6] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

GLuint vertexBufferID;
GLuint vao;
GLuint elementBufferID;

int main(int args1, const char* args2) {

	if (InitGLFW(1) > -1) {
		InitGameData();
		GameLoop(1);
	}

	return 0;
}

/*
	On Init function
*/
int InitGLFW(short verbose = 1) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow = glfwCreateWindow(2048, 1536, "Test Window", nullptr, nullptr);
	if (mainWindow == nullptr) {
		std::cerr << "Failed to create GLFW Window" << std::endl;
		ShutDown(verbose);
		return -1;
	}
	if (verbose == 1) std::cout << "Window succesfully created" << std::endl;
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to load GLAD!!";
		ShutDown(verbose);
		return -1;
	}
	if (verbose == 1) std::cout << "GLAD successfully loaded" << std::endl;

	//glViewport(0, 0, 2048, 1536);
	Scale::setViewPort(0, 0, 2048, 1536);

	//Set Callbacks
	glfwSetWindowSizeCallback(mainWindow, On_GLFW_Window_Resize);
	glfwSetCursorPosCallback(mainWindow, On_GLFW_CursorPositionMove);
	glfwSetKeyCallback(mainWindow, On_GLFW_Key_Pressed);
	return 0;
}

/*
	Application infinite loop
*/
void GameLoop(short verbose = 1) {
	if (verbose == 1) std::cout << "Launching game loop" << std::endl;
	while (!glfwWindowShouldClose(mainWindow))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLfloat currentTime = glfwGetTime();
		ProcessInput(verbose);

		glClearColor(0.3, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);

		s1->bind();
		s1->setInt("texture2D_2", 1);
		s1->setFloat("time", currentTime);
		s1->setFloat("mixThreshold", sin(currentTime * 2));
		t1->bind(0);
		t2->bind(1);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
		glBindVertexArray(NULL);
		t1->unbind();
		s1->unbind();

		ErrorChecking();

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}
}

void ErrorChecking() {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "Error: " << error << std::endl;
	}
}

void ProcessInput(short verbose = 1) {
	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(mainWindow, true);
	}
}

/*
	Shut down the Application
*/
void ShutDown(short verbose = 1) {
	if (verbose == 1) std::cout << "Shutting Down" << std::endl;
	glfwTerminate();
}

/*
	GLFW On Window Resize
*/
void On_GLFW_Window_Resize(GLFWwindow* window, int width, int height) {
	Scale::setViewPort(0, 0, width, height);
}

void On_GLFW_CursorPositionMove(GLFWwindow* window, double posX, double posY) {
	Vector2f screenCords = Scale::NormalizedScreenCordinates(Vector2f{ static_cast<float>(posX) , static_cast<float>(posY) });
	//std::cout << "Mouse Position X: " << screenCords.x << " , Y: " << screenCords.y << std::endl;
}

void On_GLFW_Key_Pressed(GLFWwindow* window , int key , int scancode , int action , int mods) {
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		textureBlendThreshold += 0.05f;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		textureBlendThreshold -= 0.05f;
	}
}

void InitGameData() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 8, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	s1 = new Shader{ "./Shaders/Default/VertexShader.vs", "./Shaders/Default/FragmentShader_s6.fs", 1 };
	t1 = new Texture{ "./Textures/awesomeface.png" , GL_RGBA };
	t2 = new Texture{ "./Textures/wall.jpg", GL_RGB };

	GLint vertexAttribLength = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribLength);
	std::cout << "Total Number of Vertex Attributes supported: " << vertexAttribLength << std::endl;
}