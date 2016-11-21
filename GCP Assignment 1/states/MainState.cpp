#include "MainState.h"

MainState::MainState(StateManager * manager, Platform * platform)
	: State(manager, platform)
{
	stateName = "Main State";

	font = TTF_OpenFont("resources/fonts/OpenSans-Regular.ttf", 16);

	plusButton = new UIButton(Vec2(10, 100), ResourceManager::getTexture("plusButton.png"));
	minusButton = new UIButton(Vec2(200, 100), ResourceManager::getTexture("minusButton.png"));
}

MainState::~MainState()
{
	TTF_CloseFont(font);

	delete plusButton;
	delete minusButton;
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
	plusButton->update(dt);
	minusButton->update(dt);
}

void MainState::render()
{
	plusButton->render(Vec2(64.0f));
	minusButton->render(Vec2(64.0f));
}
