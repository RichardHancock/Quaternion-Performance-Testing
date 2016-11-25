#include "MainState.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../misc/Mat4.h"
#include "../misc/Quat.h"
#include "../misc/MemoryCounter.h"
#include "../misc/Log.h"
#include <stdlib.h>

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
	currentTransformMode = new UITextElement(Vec2(-0.99f, -0.8f), Vec2(0.2f, -0.1f), "Matrices", Colour(255, 255, 255, 255), font);
	currentAxisLabel = new UITextElement(Vec2(0.915f, -0.82f), Vec2(0.03f, -0.09f), "X", Colour(255, 255, 255, 255), font);
	currentAngleLabel = new UITextElement(Vec2(0.9f, -0.9f), Vec2(0.06f, -0.1f), "270", Colour(255, 255, 255, 255), font);

	benchmarkTimeResult = new UITextElement(Vec2(-1.0f, 1.0f), Vec2(0.5f, -0.1f), "Benchmark Time: 00.0000s", Colour(255, 255, 255, 255), font);
	benchmarkMemoryResult = new UITextElement(Vec2(-1.0f, 0.9f), Vec2(0.6f, -0.1f), "Benchmark Memory: 00000B", Colour(255, 255, 255, 255), font);
	amountOfTransformsUI = new UITextElement(Vec2(0.4f, 1.0f), Vec2(0.6f, -0.1f), "Amount of Transforms: 1000000", Colour(255, 255, 255, 255), font);


	quatMode = false;
	benchmarkMode = false;
	benchmarkStage = NotRunning;
	currentAmountOfTransforms = 6;
	currentAxis = 0;
	currentAngle = 5;

	// Construct a projection and view matrix for the camera
	viewMat = Mat4::translate(Mat4(1.0f), Vec4(0.0f, -2.0f, -15.0f, 1.0f));
	projMat = Mat4::perspective(45.0f, 16.0f / 9.0f, 0.1f, 200.0f);
}

MainState::~MainState()
{
	TTF_CloseFont(font);

	delete modelShader;
	delete uiShader;

	delete currentMode;
	delete currentTransformMode;
	delete currentAngleLabel;
	delete currentAxisLabel;
	delete benchmarkTimeResult;
	delete benchmarkMemoryResult;
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


	//Switch between Benchmark and Animated mode
	if (InputManager::wasKeyPressed(SDLK_F1))
	{
		benchmarkMode = !benchmarkMode;
		//Swap Label
		currentMode->changeText((benchmarkMode ? "Benchmark" : "Animated"));
	}

	//Change amount of transforms being performed
	if (InputManager::wasKeyPressed(SDLK_F2) && benchmarkMode)
	{
		(currentAmountOfTransforms < 6 ? currentAmountOfTransforms++ : currentAmountOfTransforms = 0);
		//Change Label
		amountOfTransformsUI->changeText("Amount of Transforms: " + Utility::intToString(amountOfTransforms[currentAmountOfTransforms]));
	}

	//Switch between Quats and Matrices
	if (InputManager::wasKeyPressed(SDLK_F3) && benchmarkMode)
	{
		quatMode = !quatMode;
		//Swap Label
		currentTransformMode->changeText((quatMode ? "Quaternion" : "Matrices"));
	}

	//Change Axis
	if (InputManager::wasKeyPressed(SDLK_F4))
	{
		(currentAxis < 5 ? currentAxis++ : currentAxis = 0);
		//Change Label
		currentAxisLabel->changeText(axis[currentAxis]);
	}

	//Change Angle
	if (InputManager::wasKeyPressed(SDLK_F5))
	{
		(currentAngle < 6 ? currentAngle++ : currentAngle = 0);
		//Change Label
		currentAngleLabel->changeText(Utility::floatToString(angles[currentAngle], 0));
	}

	//Start Benchmark
	if (InputManager::wasKeyPressed(SDLK_SPACE) && 
		benchmarkStage != Started &&
		benchmarkMode)
	{
		benchmarkStage = Started;
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

}

void MainState::benchmarkModeUpdate(float dt)
{
	switch (benchmarkStage)
	{
	case Started:
	
		float angle = 1.0f;
		Vec3 axis(1.0f, 0.0f, 0.0f);

		long long startMemorySize = MemoryCounter::getMemoryUsage();

		uint64_t timeTaken = 0;
		//malloc(900000);
		if (quatMode)
		{
			Log::logI("Benchmark Started: " + Utility::intToString(amountOfTransforms[currentAmountOfTransforms]) + " Quaternions");
			createArrayOfQuats();

			//Start Timer
			perfTimer.startCounter();

			for (unsigned int i = 0; i < amountOfTransforms[currentAmountOfTransforms]; i++)
			{
				quatTransforms[i].rotate(angle, axis);
			}

			timeTaken = perfTimer.stopCounter();
		}
		else
		{
			Log::logI("Benchmark Started: " + Utility::intToString(amountOfTransforms[currentAmountOfTransforms]) + " Matrices");
			createArrayOfMats();

			//Start Timer
			perfTimer.startCounter();

			for (unsigned int i = 0; i < amountOfTransforms[currentAmountOfTransforms]; i++)
			{
				matTransforms[i].rotate(angle, axis);
			}

			timeTaken = perfTimer.stopCounter();
		}

		long long usedMemory = (MemoryCounter::getMemoryUsage() - startMemorySize);
		if (usedMemory == 0)
		{	
			if (quatMode)
			{
				usedMemory = sizeof(Quat) * amountOfTransforms[currentAmountOfTransforms];
			}
			else
			{
				usedMemory = sizeof(Mat4) * amountOfTransforms[currentAmountOfTransforms];
			}

			benchmarkMemoryResult->changeText("Benchmark Memory: ~" + Utility::intToString(usedMemory) + "B");
		}
		else
		{
			float usedMemoryKB = usedMemory / 1024.0f;
			benchmarkMemoryResult->changeText("Benchmark Memory: " + Utility::floatToString(usedMemoryKB, 2) + "KB");
		}
		

		Log::logI("Time Taken in Microseconds: " + Utility::intToString(timeTaken));
		float timeTakenMilliSeconds = (timeTaken / 1000.0f);
		benchmarkTimeResult->changeText("Benchmark Time: " + Utility::floatToString(timeTakenMilliSeconds, 4) + "ms");

		benchmarkStage = Completed;
		matTransforms.clear();
		quatTransforms.clear();
		//This makes sure the memory is released
		matTransforms.shrink_to_fit();
		quatTransforms.shrink_to_fit();
		break;
	}
}

void MainState::createArrayOfQuats()
{
	for (unsigned int i = 0; i < amountOfTransforms[currentAmountOfTransforms]; i++)
	{
		quatTransforms.push_back(Quat(1.0f, 0.0f, 0.0f, 0.0f));
	}
	
}

void MainState::createArrayOfMats()
{
	for (unsigned int i = 0; i < amountOfTransforms[currentAmountOfTransforms]; i++)
	{
		matTransforms.push_back(Mat4(1.0f));
	}
}

void MainState::render()
{
	Mat4 modelMatrix = Mat4(1.0f);
	//modelMatrix.rotate(-2.0f, Vec3(0.0f, 0.0f, 1.0f));
	//modelMatrix = Mat4::rotateY(modelMatrix, -rotation);
	//modelMatrix = Mat4::rotateZ(modelMatrix, rotation);

	Quat rotate = Quat(1.0f, 0, 0, 0);
	rotate = rotate.rotate(-2.0f, Vec3(0.0f, 0.0f, 1.0f));
	//Quat rotateY = Quat(1.0f, 0, 0, 0);
	//rotateY = rotateY.rotate(rotation, Vec3(0.0f, 1.0f, 0.0f));
	//Quat rotateZ = Quat(1.0f, 0, 0, 0);
	//rotateZ = rotateZ.rotate(rotation, Vec3(0.0f, 0.0f, 1.0f));
	//rotate = rotate * rotateY * rotateZ;
	
	

	modelMatrix = rotate.getMat();// * rotateY.getMat()// * rotateZ.getMat();
	//modelMatrix.z.w = -10.0f;

	
	test->draw(modelMatrix, viewMat, projMat, modelShader);

	currentMode->draw(uiShader);
	currentAngleLabel->draw(uiShader);
	currentAxisLabel->draw(uiShader);

	amountOfTransformsUI->draw(uiShader);

	if (benchmarkMode)
	{
		currentTransformMode->draw(uiShader);
		benchmarkTimeResult->draw(uiShader);
		benchmarkMemoryResult->draw(uiShader);
	}
	
}