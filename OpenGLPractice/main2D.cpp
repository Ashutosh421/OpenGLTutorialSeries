#include <iostream>
#include <memory>
#include <glad\glad.h>
#include "Core\Application.h"
#include "Core\InputManager.h"
#include "Core\SceneManager.h"
#include "Core\Entity.h"
#include "Core\2D\Shapes2D\Rectangle\Rectangle.h"
#include "Core\2D\MeshRenderer2D\MeshRenderer2D.h"

std::shared_ptr<AR::Rectangle> gameObject1;
std::shared_ptr<AR::Scene> scene1;

void InitScene();
void InitializeSceneObjects();
void ErrorChecking();

int main(int args1, char **args2) {
	if (AR::Application::Instance()->Init()) {
		InitScene();

		while (AR::Application::Instance()->IsRunning()) {
			AR::SceneManager::Update();
			AR::Application::Instance()->Update();
			ErrorChecking();
		}
		AR::Application::Instance()->Stop();
	}
	return 0;
}

void InitScene() {
	scene1 = std::make_shared<AR::Scene>("Scene1");

	AR::InputManager::SetCurrentWindow(AR::Application::Instance()->Window());
	AR::SceneManager::AddScene(std::move(scene1));
	AR::SceneManager::LoadScene(scene1->Name());

	scene1->backgroudColor.r = 0.2f;
	scene1->backgroudColor.g = 0.2f;
	scene1->backgroudColor.b = 0.2f;
	scene1->backgroudColor.a = 0.2f;
	
	InitializeSceneObjects();
}

void InitializeSceneObjects() {
	gameObject1 = std::make_shared<AR::Rectangle>("Rectangle1", 1);
	scene1->AddChild(std::move(gameObject1));
}

void ErrorChecking() {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "Error: " << error << std::endl;
	}
}