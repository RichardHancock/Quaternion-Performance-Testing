#include "MainState.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../misc/Mat4.h"
#include "../misc/Quat.h"
#include "../misc/MemoryCounter.h"
#include "../misc/PerformanceCounter.h"
#include "../misc/Log.h"

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
	xLabel = new UITextElement(Vec2(0.71f, -0.84f), Vec2(0.03f, -0.07f), "X", Colour(255, 255, 255, 255), font);
	yLabel = new UITextElement(Vec2(0.81f, -0.84f), Vec2(0.03f, -0.07f), "Y", Colour(255, 255, 255, 255), font);
	zLabel = new UITextElement(Vec2(0.91f, -0.84f), Vec2(0.03f, -0.07f), "Z", Colour(255, 255, 255, 255), font);
	xCurrent = new UITextElement(Vec2(0.7f, -0.9f), Vec2(0.05f, -0.1f), "100", Colour(255, 255, 255, 255), font);
	yCurrent = new UITextElement(Vec2(0.8f, -0.9f), Vec2(0.05f, -0.1f), "100", Colour(255, 255, 255, 255), font);
	zCurrent = new UITextElement(Vec2(0.9f, -0.9f), Vec2(0.05f, -0.1f), "100", Colour(255, 255, 255, 255), font);

	benchmarkResult = new UITextElement(Vec2(-1.0f, 1.0f), Vec2(0.4f, -0.1f), "Benchmark Result: N/A", Colour(255, 255, 255, 255), font);
	amountOfTransformsUI = new UITextElement(Vec2(0.4f, 1.0f), Vec2(0.6f, -0.1f), "Amount of Transforms: 1000000", Colour(255, 255, 255, 255), font);


	benchmarkMode = false;
	benchmarkStage = NotRunning;
	amountOfTransforms = 1000000;
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
	delete benchmarkResult;
	delete amountOfTransformsUI;
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

	if (InputManager::wasKeyPressed(SDLK_SPACE))
	{
		benchmarkMode = !benchmarkMode;
	}

	return false;
}

void MainState::update(float dt)
{
	

	if (!benchmarkMode)
	{
		rotation += 1.0f * dt;
	}
	else
	{
		benchmarkModeUpdate(dt);
	}


	if (InputManager::wasKeyPressed(SDLK_t))
	{
		matTransforms.clear();
		float size = MemoryCounter::getMemoryUsage();
		Log::logI("Mem Usage: " + Utility::floatToString(size) + "MB");
		createArrayOfMats();
		size = MemoryCounter::getMemoryUsage();
		Log::logI("Mem Usage: " + Utility::floatToString(size) + "MB");
	}

}

void MainState::benchmarkModeUpdate(float dt)
{
	switch (benchmarkStage)
	{
	case Started:
		matTransforms.clear();
		quatTransforms.clear();

		if (!quatMode)
		{
			
		}
		break;
	}
}

void MainState::createArrayOfQuats()
{
	for (unsigned int i = 0; i < amountOfTransforms; i++)
	{
		quatTransforms.push_back(Quat(1.0f, 0.0f, 0.0f, 0.0f));
	}
}

void MainState::createArrayOfMats()
{
	for (unsigned int i = 0; i < amountOfTransforms; i++)
	{
		matTransforms.push_back(Mat4(1.0f));
	}
}

void MainState::render()
{
	Mat4 modelMatrix = Mat4(1.0f);
	//modelMatrix.x.w = 5.0f;
	//modelMatrix = Mat4::rotateX(modelMatrix, rotation);
	//modelMatrix = Mat4::rotateY(modelMatrix, -rotation);
	//modelMatrix = Mat4::rotateZ(modelMatrix, rotation);

	Quat rotate = Quat(1.0f, 0, 0, 0);
	rotate = rotate.rotate(rotation, Vec3(0.0f, 0.0f, 1.0f));
	//Quat rotateY = Quat(1.0f, 0, 0, 0);
	//rotateY = rotateY.rotate(rotation, Vec3(0.0f, 1.0f, 0.0f));
	//Quat rotateZ = Quat(1.0f, 0, 0, 0);
	//rotateY = rotateY.rotate(rotation, Vec3(0.0f, 0.0f, 1.0f));
	//rotate = rotate * rotateY;
	

	modelMatrix = rotate.getMat();// * rotateY.getMat() * rotateZ.getMat();
	modelMatrix.z.w = -10.0f;

	Mat4 viewMatrix = Mat4::translate(Mat4(1.0f), Vec4(0.0f, -2.0f, -10.5f, 1.0f));

	// Construct a projection matrix for the camera
	glm::mat4 projMatrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 200.0f);

	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 0.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = -10.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.z.w = -10.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 0.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	modelMatrix.x.w = 10.0f;
	test->draw(modelMatrix, viewMatrix, projMatrix, modelShader);

	currentMode->draw(uiShader);
	xLabel->draw(uiShader);
	yLabel->draw(uiShader);
	zLabel->draw(uiShader);
	xCurrent->draw(uiShader);
	yCurrent->draw(uiShader);
	zCurrent->draw(uiShader);

	benchmarkResult->draw(uiShader);
	amountOfTransformsUI->draw(uiShader);
}