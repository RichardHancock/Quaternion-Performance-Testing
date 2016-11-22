#pragma once

#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <GL/glew.h>

#include "misc/Vec2.h"

/** @brief Class that handles the initialization of SDL 2 (and its add ons) across all supported platforms */
class Platform
{
public:

	/**
	@brief Constructor.
	*/
	Platform();

	/** @brief Destructor, Calls SDL's cleanup features for itself and its add ons. */
	~Platform();

	/**
	@brief Initialises the SDL library and its plugins, for the current platform.
	
	@param openGL true to use openGL instead of the 2D SDL renderer.
	
	@return bool - Was successful.
	 */
	bool initSDL(bool openGL);

	/**
	 @brief Gets the window.
	
	 @return null if it fails, else the window.
	 */
	SDL_Window* getWindow() { return window; }

	/**
	@brief Gets the SDL 2D renderer.
	Not initialized if OpenGL was requested

	@return nullptr if it fails, else the renderer.
	 */
	SDL_Renderer* getRenderer();
	
	/**
	@brief Gets the GL context.
	
	@return null if it fails, else the context.
	 */
	SDL_GLContext getContext();

	/**
	 @brief Gets window size.
	
	 @return The window size.
	 */
	Vec2 getWindowSize() { return windowSize; }


	/** @brief Outputs the linked and compiled SDL version numbers into the log. */
	void printSDLVersion();


	bool isFeatureSupported(std::string feature);
	
private:

	/**
	@brief Initialises glew.

	@return true if it succeeds, false if it fails.
	*/
	bool initGLEW();

	/** @brief The window. */
	SDL_Window* window;


	/** @brief The 2D SDL renderer. Not created with OpenGL enabled */
	SDL_Renderer* renderer;

	/** @brief The GL context. */
	SDL_GLContext context;

	/** @brief Size of the window. */
	Vec2 windowSize;

	//The resolution everything is scaled from
	const Vec2 scale;

	//Platform Feature Support (Wraps SDL CPU feature detection)
	std::unordered_map<std::string, bool> features;

	void checkFeatureSupport();

	
};