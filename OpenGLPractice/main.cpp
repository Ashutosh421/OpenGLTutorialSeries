#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/opencv.hpp>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>B

#include "Core\Vertex.h"
#include "Core/Shader.h"
#include "Utilities/Scale/Scale.h"
#include "Core/Texture.h"
#include "Core/Time.h"
#include "Core/Camera.h" 

Shader* s1;
Texture* t1;
Texture* t2;
glm::vec2 mouseScreenCordinates{0.0f , 0.0f};
glm::vec2 mouseDelta{0.0f , 0.0f};
float pitch = 0.0f;
float yaw = -90.0f;
bool lockCamera = false;
bool firstMouse = false;

GLFWwindow* mainWindow;
int InitGLFW(short);
void InitGameData();
void LoadAssimpMesh();
void GameLoop(short);
void ProcessInput(short);
void ShutDown(short);
void ErrorChecking();

//GLFWCallbacks
void On_GLFW_Window_Resize(GLFWwindow* , int , int);
void On_GLFW_CursorPositionMove(GLFWwindow*, double, double);
void On_GLFW_Key_Pressed(GLFWwindow*, int, int , int , int);
void On_GLFW_Scrolled(GLFWwindow*, double, double);

glm::vec3 cameraPosition{0.0f , 0.0f , 13.0f};


std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

std::vector<ar::Vertex> susanSceneVertices;
std::vector<GLuint> susanIndices;

std::vector<GLubyte> indices ={
//GLubyte indices[6] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

std::vector<glm::vec3> cubePositions = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
};

 
GLuint vertexBufferID;
GLuint vao;
GLuint elementBufferID;
glm::mat4 transform, view, projection; 
Camera mainCamera;

Assimp::Importer aImporter;



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
	glfwSetWindowSizeCallback(mainWindow , On_GLFW_Window_Resize);
	glfwSetCursorPosCallback(mainWindow, On_GLFW_CursorPositionMove);
	glfwSetKeyCallback(mainWindow, On_GLFW_Key_Pressed);
	glfwSetScrollCallback(mainWindow, On_GLFW_Scrolled);
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
		Time::Update();

		glClearColor(0.3f, 0.3f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);

		s1->bind();

		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f));
		transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

		s1->setMat4("model", transform);
		s1->setMat4("view", mainCamera.getViewMatrix());
		s1->setMat4("projection", mainCamera.getProjectionMatrix());

		//glDrawArrays(GL_TRIANGLES, 0, susanSceneVertices.size());
		glDrawElements(GL_TRIANGLES, susanIndices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(NULL);
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

	float cameraSpeed = 4.0f;

	if (glfwGetKey(mainWindow, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS) {
		mainCamera.position += cameraSpeed * mainCamera.cameraFront * Time::deltaTime;
	}
	if (glfwGetKey(mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS) {
		mainCamera.position -= cameraSpeed * mainCamera.cameraFront * Time::deltaTime;
	}
	if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS) {
		mainCamera.position += glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed * Time::deltaTime;
	}
	if (glfwGetKey(mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS) {
		mainCamera.position -= glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed * Time::deltaTime;
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
void On_GLFW_Window_Resize(GLFWwindow* window , int width , int height) {
	Scale::setViewPort(0, 0, width, height);
}

void On_GLFW_CursorPositionMove(GLFWwindow* window, double posX, double posY) {
	//Vector2f screenCords = Scale::NormalizedScreenCordinates(Vector2f{ static_cast<float>(posX) , static_cast<float>(posY)});
	if (lockCamera) {
		glm::vec2 currentPos = glm::vec2{ posX , posY };
		if (!firstMouse) {
			mouseScreenCordinates = currentPos;
			firstMouse = true;
		}
		mouseDelta.x = currentPos.x - mouseScreenCordinates.x;
		mouseDelta.y = mouseScreenCordinates.y - currentPos.y;
		mouseScreenCordinates = currentPos;
		
		mouseDelta *= 0.05f;

		pitch += (mouseDelta.y);
		yaw += (mouseDelta.x);

		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		//std::cout << "Front" << "X: " << front.x << "Y: " << front.y << "Z: " << front.z << std::endl;
		mainCamera.cameraFront = glm::normalize(front);
	}
}

void On_GLFW_Key_Pressed(GLFWwindow*, int key, int scancode, int action, int mode) {
	if (glfwGetKey(mainWindow, GLFW_KEY_TAB) == GLFW_PRESS) {
		if (glfwGetKey(mainWindow, GLFW_KEY_TAB) == GLFW_PRESS) {
			lockCamera = !lockCamera;
			if (lockCamera)
			{
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				firstMouse = false;
			}
			else
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			std::cout << "Lock Camera" << lockCamera << std::endl;
		}
	}
}

void On_GLFW_Scrolled(GLFWwindow*, double x, double y) {
	mainCamera.UpdateProjectionMatrix(mainCamera.Field_Of_View() - y);
}

void InitGameData() {
	LoadAssimpMesh();
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, susanSceneVertices.size() * 8 * sizeof(GLfloat), &susanSceneVertices[0].position.x, GL_STATIC_DRAW);

	glGenBuffers(1, &elementBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, susanIndices.size() * sizeof(GLuint), &susanIndices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 8, (void*)(2 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	s1 = new Shader{ "./Shaders/Default/VertexShader.vs", "./Shaders/Default/FragmentShader.fs", 1 };
	
	GLint vertexAttribLength = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribLength);
	std::cout << "Total Number of Vertex Attributes supported: " << vertexAttribLength << std::endl;

	mainCamera.position = glm::vec3(0.0f, 0.0f, 10.0f);
}

void LoadAssimpMesh() {
	const aiScene *aScene = aImporter.ReadFile("./Models/Fbx/Susan.fbx", aiProcess_TransformUVCoords | aiProcess_FlipUVs);
	
	if (!aScene || aScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aScene->mRootNode) {
		std::cout << "Error Reading FBX file: " << aImporter.GetErrorString() << std::endl;
		return;
	}

	if (aScene->HasMeshes()) {
		std::cout << "Total Meshes loaded: " << aScene->mNumMeshes << std::endl;
		for (unsigned int i = 0; i < aScene->mNumMeshes; i++) {
			aiMesh *mesh = aScene->mMeshes[i];
			if (mesh->HasPositions()) {
				for (unsigned int j = 0; j < mesh->mNumVertices; j++)
				{
					aiVector3D position = mesh->mVertices[j];
					susanSceneVertices.emplace_back(ar::Vertex(glm::vec3(position.x , position.y , position.z)));
				}
			}
			if (mesh->HasFaces()) {
				for (unsigned int k = 0; k < mesh->mNumFaces; k++) {
					aiFace face = mesh->mFaces[k];
					for (unsigned int ind = 0; ind < face.mNumIndices; ind++) {
						susanIndices.push_back(face.mIndices[ind]);
					}
				}
			}
		}
		std::cout << "Total Susan Vertices: " << susanSceneVertices.size() << std::endl;
		std::cout << "Total Susan Indices: " << susanIndices.size() << std::endl;
	}
}