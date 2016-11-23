#pragma once

#include "State.h"

#include <SDL_ttf.h>

#include "../misc/Quat.h"

class MainState : public State
{
public:
	/**
	@brief Create the State.

	@param [in,out] manager		    Pointer to the current state manager.
	@param [in,out] platform	    Pointer to platform.
	*/
	MainState(StateManager* manager, Platform* platform);

	virtual ~MainState();

	/**
	@brief Handles any events such as keyboard/mouse input
	@return Continue the game
	*/
	virtual bool eventHandler();

	/**
	@brief Update any internal values
	@param dt delta time
	*/
	virtual void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	virtual void render();

private:

	TTF_Font* font;
	float rotation;
	Shader* modelShader;
	Shader* uiShader;

	Quat* currentRotate;

	GameModel* test;
};