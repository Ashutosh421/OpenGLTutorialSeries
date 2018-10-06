#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Core/Shader/Shader.h"

Shader* s1;
Shader* s2;

GLFWwindow* mainWindow;
int InitGLFW(short);
void InitGameData();
void GameLoop(short);
void ProcessInput(short);
void ShutDown(short);
void ErrorChecking();

//GLFWCallbacks
void On_GLFW_Window_Resize(GLFWwindow*, int, int);

GLfloat verticesTri_1[] = {
	 0.0f,  0.5f, 0.0f,  // top right
	 0.0f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
};

GLfloat verticesTri_2[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	0.0f, -0.5f, 0.0f,  // bottom left
};

GLuint vertexBufferID_1;
GLuint vertexArrayObject_1;

GLuint vertexBufferID_2;
GLuint vertexArrayObject_2;


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

		s1->bind();
		glBindVertexArray(vertexArrayObject_1);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesTri_1) / 3);
		glBindVertexArray(NULL);
		
		s2->bind();
		glBindVertexArray(vertexArrayObject_2);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesTri_2) / 3);
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
	//Preparing the first the vertex Array Object
	glGenVertexArrays(1, &vertexArrayObject_1);
	glBindVertexArray(vertexArrayObject_1);

	//Preparing the first vertex Buffer object
	glGenBuffers(1, &vertexBufferID_1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri_1), verticesTri_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 3, (void*)(0));
	glEnableVertexAttribArray(0);


	//Preparing the second Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObject_2);
	glBindVertexArray(vertexArrayObject_2);

	//Preparing the second vertex buffer object
	glGenBuffers(1, &vertexBufferID_2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayObject_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri_2), verticesTri_2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	s1 = new Shader{ "./Shaders/Default/VertexShader.vs", "./Shaders/Default/FragmentShader.fs", 1 };
	s2 = new Shader{ "./Shaders/Default/VertexShader.vs", "./Shaders/Default/FragmentShader_s2.fs", 1 };

}