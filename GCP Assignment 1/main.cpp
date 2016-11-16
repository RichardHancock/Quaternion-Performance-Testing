#include <SDL.h>

#include "Platform.h"
#include "misc/Utility.h"
#include "misc/Log.h"
#include "states/StateManager.h"
#include "ResourceManager.h"
#include "input/InputManager.h"

#ifdef _WIN32
#include <windows.h>

//This forces NVIDIA hybrid GPU's (Intel and Nvidia integrated) to use the high performance NVidia chip rather than the Intel.
//This was recommended by NVidia's policies: http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C" 
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif


int main(int, char**);
void processCommandLine(int argc, char** argv);


int main(int argc, char **argv)
{	
	processCommandLine(argc, argv);

	//Initialise platform class and all dependencies
	Platform* platform = new Platform();

	if (!platform->initSDL(false))
	{
		Log::logE("SDL Failed to initialize");
		exit(1);
	}

	
	Utility::randomInit();

	SDL_Window* window = platform->getWindow();

	SDL_Renderer* renderer = platform->getRenderer();
	SDL_RenderSetLogicalSize(renderer, 1280, 720);

	StateManager* stateManager = new StateManager((int)platform->getWindowSize().x, (int)platform->getWindowSize().y);
	
	ResourceManager::setRenderer(renderer);

	unsigned int lastTime = SDL_GetTicks();

	bool quit = false;
	
	while (!quit)
	{
		//Event/Input Handling
		quit = stateManager->eventHandler();

		//Update
		//DT Calc
		unsigned int current = SDL_GetTicks();
		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		Utility::Timer::update(dt);
		stateManager->update(dt);

		InputManager::update();
		ResourceManager::update(dt);

		//Render
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		stateManager->render();

		SDL_RenderPresent(renderer);

		if (dt < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - dt)*1000.0f));
		}
	}

	delete stateManager;
	InputManager::cleanup();
	ResourceManager::cleanup();
	delete platform;
	SDL_Quit();

	exit(0);
}

void processCommandLine(int argc, char **argv)
{
	Log::logI("No command line arguments are handled currently");
	Log::logI("These were the passed in args:");
	
	for (int i = 1; i < argc; i++)
	{
		Log::logI(argv[i]);
	}
}