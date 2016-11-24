#pragma once

#include "State.h"

#include <SDL_ttf.h>

#include "../misc/Quat.h"
#include "../ui/UI.h"

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

	void benchmarkModeUpdate(float dt);

	void createArrayOfQuats();

	void createArrayOfMats();

	/**
	@brief Render any sprites relevant to the state
	*/
	virtual void render();

private:

	enum BenchmarkStage
	{
		NotRunning,
		Started,
		Completed
	};

	TTF_Font* font;
	float rotation;
	Shader* modelShader;
	Shader* uiShader;

	GameModel* test;

	bool benchmarkMode;
	BenchmarkStage benchmarkStage;
	bool quatMode;

	unsigned int amountOfTransforms;

	std::vector<Quat> quatTransforms;
	std::vector<Mat4> matTransforms;

	UITextElement* currentMode;
	UITextElement* xLabel;
	UITextElement* yLabel;
	UITextElement* zLabel;

	UITextElement* xCurrent;
	UITextElement* yCurrent;
	UITextElement* zCurrent;

	UITextElement* benchmarkResult;
	UITextElement* amountOfTransformsUI;
};