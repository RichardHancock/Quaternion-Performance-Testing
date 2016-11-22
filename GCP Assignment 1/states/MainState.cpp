#include "MainState.h"

#include "glm/gtc/matrix_transform.hpp"

MainState::MainState(StateManager * manager, Platform * platform)
	: State(manager, platform)
{
	stateName = "Main State";

	font = TTF_OpenFont("resources/fonts/OpenSans-Regular.ttf", 16);

	std::string shaderDir = ResourceManager::shaderDir;
	modelShader = new Shader(shaderDir + "standardVertex.shader", shaderDir + "standardFrag.shader");
	uiShader = new Shader(shaderDir + "2D vertex.shader", shaderDir + "2D fragment.shader");

	test = ResourceManager::getModel("barrel.obj", ResourceManager::getTexture("barrel.png"));
}

MainState::~MainState()
{
	TTF_CloseFont(font);

	delete modelShader;
	delete uiShader;
}

bool MainState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return true;
			break;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			InputManager::processKeyEvent(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			InputManager::processMouseEvent(e);

			break;

		case SDL_CONTROLLERAXISMOTION:
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
			InputManager::processGameControllerEvent(e);
			break;
		}
	}

	if (InputManager::wasKeyReleased(SDLK_ESCAPE))
	{
		return true;
	}

	return false;
}

void MainState::update(float dt)
{

}

void MainState::render()
{

	glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1), glm::vec3(0, -2.0f, -10.5f));

	// Construct a projection matrix for the camera
	glm::mat4 projMatrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 200.0f);

	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);
}
