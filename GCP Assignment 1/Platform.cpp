#include "Platform.h"

#include <string>
#include <fstream>

#include "misc/Log.h"
#include "misc/Utility.h"


Platform::Platform()
	: scale(Vec2(1280, 720))
{
	window = nullptr;
	renderer = nullptr;
}

Platform::~Platform()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();

	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	SDL_DestroyWindow(window);
}

bool Platform::initSDL(bool openGL)
{
	///@todo abort program on every error rather than just waiting

	bool status = true;
	
	//Android doesn't need this at SDL internally does this
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0) 
	{ 
		status = false; 
		Log::logE("SDL Init failed: " + std::string(SDL_GetError()));
	}
	
	//SDL Version Information for Debug
	printSDLVersion();


	//SDL TTF Initialization
	if (TTF_Init() < 0)
	{
		status = false;
		Log::logE("SDL_ttf init failed: " + std::string(TTF_GetError()));
	}

	//SDL Mixer Initialization
	Mix_Init(MIX_INIT_OGG);
	//Initialize SDL_Mixer with some standard audio formats/freqs. Also set channels to 2 for stereo sound.
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		status = false;
		Log::logE("SDL_mixer init failed: " + std::string(Mix_GetError()));
	}
	
	//SDL Image Initialization
	int flags= IMG_INIT_PNG;
	int result = IMG_Init(flags);
	
	// If the inputed flags are not returned, an error has occurred
	if((result & flags) != flags) 
	{
		Log::logE("Failed to Initialise SDL_Image and png support: "+ std::string(IMG_GetError()));
	}
	

	uint32_t windowFlags = SDL_WINDOW_OPENGL;
	windowSize = Vec2(1280, 720);

	window = SDL_CreateWindow(
		"GCP Assignment 1",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		(int) windowSize.x, 
		(int) windowSize.y,
		windowFlags
		);


	if (!window) 
	{ 
		status = false;
		Log::logE("Window failed to be created: " + 
			std::string(SDL_GetError()));
	}
	

	renderer = SDL_CreateRenderer(window, -1, 0);
		
	if (renderer == nullptr)
	{
		Log::logE("SDL Renderer failed to be created: " + std::string(SDL_GetError()));
		status = false;
	}
	

	int width;
	int height;

	SDL_GetWindowSize(window, &width, &height);

	windowSize.x = (float)width;
	windowSize.y = (float)height;
	
	Log::logI("Window Dimensions: " + Utility::intToString(width) +
		"x" + Utility::intToString(height));

	//Feature Detection
	checkFeatureSupport();

	//Platform Details
	Log::logI("CPU Cores: " + Utility::intToString(SDL_GetCPUCount()));
	Log::logI("CPU L1 Cache: " + Utility::intToString(SDL_GetCPUCacheLineSize()) + "KB");
	Log::logI("RAM: " + Utility::intToString(SDL_GetSystemRAM()) + "MB");


	return status;
}


SDL_Renderer* Platform::getRenderer()
{
	if (renderer != nullptr)
	{
		return renderer;
	}
	else
	{
		Log::logE("SDL Renderer requested but it does not exist (Due to either an error or OpenGL being requested instead)");
		return nullptr;
	}
}

SDL_GLContext Platform::getContext()
{
	if (context != 0)
	{
		return context;
	}
	else
	{
		Log::logE("OpenGL Context requested but it does not exist (Due to either an error or OpenGL not being requested)");
		return 0;
	}
}


void Platform::printSDLVersion()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	Log::logI("SDL Version:");
	Log::logI("Compiled: " + Utility::sdlVersionToString(compiled));
	Log::logI("Linked: " + Utility::sdlVersionToString(linked));
}

bool Platform::isFeatureSupported(std::string feature)
{
	if (features.count(feature) == 0)
	{
		Log::logW(feature + " feature is unknown, assuming unsupported.");
		return false;
	}

	return features[feature];
}

void Platform::checkFeatureSupport()
{
	features["3DNow"] = SDL_Has3DNow() == SDL_TRUE;
	features["AVX"] = SDL_HasAVX() == SDL_TRUE;
	features["AVX2"] = SDL_HasAVX2() == SDL_TRUE;
	features["AltiVec"] = SDL_HasAltiVec() == SDL_TRUE;
	features["MMX"] = SDL_HasMMX() == SDL_TRUE;
	features["RDTSC"] = SDL_HasRDTSC() == SDL_TRUE;
	features["SSE"] = SDL_HasSSE() == SDL_TRUE;
	features["SSE2"] = SDL_HasSSE2() == SDL_TRUE;
	features["SSE3"] = SDL_HasSSE3() == SDL_TRUE;
	features["SSE41"] = SDL_HasSSE41() == SDL_TRUE;
	features["SSE42"] = SDL_HasSSE42() == SDL_TRUE;

	Log::logI("Platform Features:");
	for (auto feature : features)
	{
		Log::logI(" - " + feature.first + ": " + (feature.second ? "Yes" : "No"));
	}
}