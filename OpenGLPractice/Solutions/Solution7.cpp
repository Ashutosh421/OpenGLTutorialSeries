#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../Core/Shader.h"
#include "../Utilities/Scale/Scale.h"
#include "../Core/Texture.h"
#include <opencv2/opencv.hpp>

Shader* s1;
Texture* t1;
Texture* t2;
Vector2f mouseScreenCordinates;

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

//std::vector<GLfloat> vertices = {
//	//GLfloat vertices[] = {
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
//};
//
//std::vector<GLubyte> indices = {
//	//GLubyte indices[6] = {
//		0, 1, 3,   // first triangle
//		1, 2, 3    // second triangle
//};

std::vector<GLfloat> triVertices = {
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,     1.0f , 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,     0.0f , 0.0f, // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,     0.5f , 1.0f   // top 
};

std::vector<GLubyte> triIndices = {
	0, 1, 2
};

GLuint vertexBufferID;
GLuint vao;
GLuint elementBufferID;
glm::mat4 transform;


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

		glClearColor(0.3f, 0.3f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);

		s1->bind();
		s1->setInt("texture2D_2", 1);
		s1->setFloat("time", currentTime);
		t1->bind(0);
		t2->bind(1);

		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 1.0f));
		transform = glm::rotate(transform, currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));

		//s1->setMat4("modelMatrix", transform);


		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
		

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

void InitGameData() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, triVertices.size() * sizeof(GLfloat), &triVertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triIndices.size() * sizeof(GLubyte), &triIndices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	s1 = new Shader{ "./Shaders/Default/VertexShader.vs", "./Shaders/Default/FragmentShader.fs", 1 };
	t1 = new Texture{ "./Textures/awesomeface.png" , GL_RGBA };
	t2 = new Texture{ "./Textures/wall.jpg", GL_RGB };

	GLint vertexAttribLength = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribLength);
	std::cout << "Total Number of Vertex Attributes supported: " << vertexAttribLength << std::endl;


}