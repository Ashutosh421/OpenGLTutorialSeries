#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "../Core/Shader.h"
#include "../Math/Vector2f.h"
//#include "../Core/Vertex/Vertex.h"

Shader* s1;

GLFWwindow* mainWindow;
int InitGLFW(short);
void InitGameData();
void GameLoop(short);
void ProcessInput(short);
void ShutDown(short);
void ErrorChecking();

//GLFWCallbacks
void On_GLFW_Window_Resize(GLFWwindow*, int, int);

GLfloat vertices[] = {
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};

GLubyte indices[] = {
	0, 1, 2
};

GLuint vertexBufferID;
GLuint vao;
GLuint elementBufferID;

GLuint horiUniformLocation;

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

	glViewport(0, 0, 2048, 1536);

	//Set Callbacks
	glfwSetWindowSizeCallback(mainWindow, On_GLFW_Window_Resize);
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
		ProcessInput(verbose);

		glClearColor(0.3, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);

		s1->bind();

		GLfloat currentTime = glfwGetTime();

		//glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
		glUniform2f(horiUniformLocation, sin(currentTime * 2) / 2, cos(currentTime * 2) / 2);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
		glBindVertexArray(NULL);

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
	std::cout << "Resizing: " << width << " , " << height << std::endl;
	glViewport(0, 0, width, height);
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 6, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	s1 = new Shader{ "./Shaders/Default/VertexShader_s5.vs", "./Shaders/Default/FragmentShader_s5.fs", 1 };

	GLint vertexAttribLength = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribLength);
	std::cout << "Total Number of Vertex Attributes supported: " << vertexAttribLength << std::endl;

	horiUniformLocation = glGetUniformLocation(s1->shaderProgram, "horiOffset");
}