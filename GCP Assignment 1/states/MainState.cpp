#include "MainState.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../misc/Mat4.h"
#include "../misc/Quat.h"

MainState::MainState(StateManager * manager, Platform * platform)
	: State(manager, platform)
{
	stateName = "Main State";

	font = TTF_OpenFont("resources/fonts/OpenSans-Regular.ttf", 24);

	std::string shaderDir = ResourceManager::shaderDir;
	modelShader = new Shader(shaderDir + "standardVertex.shader", shaderDir + "standardFrag.shader");
	uiShader = new Shader(shaderDir + "2D vertex.shader", shaderDir + "2D fragment.shader");

	test = ResourceManager::getModel("barrel.obj", ResourceManager::getTexture("barrel.png"));
	rotation = 0;

	currentMode = new UITextElement(Vec2(-0.99f, -0.9f), Vec2(0.2f, -0.1f), "Animated", Colour(255, 255, 255, 255), font);
	xLabel = new UITextElement(Vec2(0.7f, -0.8f), Vec2(0.03f, -0.07f), "X", Colour(255, 255, 255, 255), font);
	yLabel = new UITextElement(Vec2(0.8f, -0.8f), Vec2(0.03f, -0.07f), "Y", Colour(255, 255, 255, 255), font);
	zLabel = new UITextElement(Vec2(0.9f, -0.8f), Vec2(0.03f, -0.07f), "Z", Colour(255, 255, 255, 255), font);
	xCurrent = new UITextElement(Vec2(0.7f, -0.9f), Vec2(0.05f, -0.1f), "10", Colour(255, 255, 255, 255), font);
	yCurrent = new UITextElement(Vec2(0.8f, -0.9f), Vec2(0.05f, -0.1f), "10", Colour(255, 255, 255, 255), font);
	zCurrent = new UITextElement(Vec2(0.9f, -0.9f), Vec2(0.05f, -0.1f), "10", Colour(255, 255, 255, 255), font);
}

MainState::~MainState()
{
	TTF_CloseFont(font);

	delete modelShader;
	delete uiShader;

	delete currentMode;
	delete xLabel;
	delete yLabel;
	delete zLabel;
	delete xCurrent;
	delete yCurrent;
	delete zCurrent;
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
	rotation += 1.0f * dt;
}

void MainState::render()
{
	Mat4 modelMatrix = Mat4(1.0f);
	modelMatrix.x.w = 5.0f;
	modelMatrix = Mat4::rotateX(modelMatrix, rotation);
	modelMatrix = Mat4::rotateY(modelMatrix, -rotation);
	modelMatrix = Mat4::rotateZ(modelMatrix, rotation);

	//Quat rotate = Quat(1.0f, 0, 0, 0);
	//rotate = rotate.rotate(2.0f, Vec3(1.0f, 1.0f, 0.0f));
	//Quat rotateY = Quat(1.0f, 0, 0, 0);
	//rotateY = rotateY.rotate(rotation, Vec3(0.0f, 1.0f, 0.0f));
	//Quat rotateZ = Quat(1.0f, 0, 0, 0);
	//rotateY = rotateY.rotate(rotation, Vec3(0.0f, 0.0f, 1.0f));
	//rotate = rotate * rotateY;
	

	//modelMatrix = rotate.getMat();// * rotateY.getMat() * rotateZ.getMat();
	//modelMatrix.z.w = -10.0f;

	Mat4 viewMatrix = Mat4::translate(Mat4(1.0f), Vec4(0.0f, -2.0f, -10.5f, 1.0f));

	// Construct a projection matrix for the camera
	glm::mat4 projMatrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 200.0f);

	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 0.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = -5.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.z.w = -10.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 0.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 5.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	currentMode->draw(uiShader);
	xLabel->draw(uiShader);
	yLabel->draw(uiShader);
	zLabel->draw(uiShader);
	xCurrent->draw(uiShader);
	yCurrent->draw(uiShader);
	zCurrent->draw(uiShader);
}