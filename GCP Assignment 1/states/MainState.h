#pragma once

#include "State.h"

#include <SDL_ttf.h>

#include "../misc/Quat.h"
#include "../ui/UI.h"
#include "../misc/PerformanceCounter.h"

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

	void benchmarkModeUpdate(float dt);

	void createArrayOfQuats();

	void createArrayOfMats();

	Vec4 determineRotation();

	void prepareTransformsForRender();

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

	PerformanceCounter perfTimer;

	unsigned int currentAmountOfTransforms;
	const unsigned int amountOfTransforms[7] = 
	{
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
	};

	const float angles[7] =
	{
		10,
		30,
		45,
		90,
		180,
		270,
		360,
	};

	const std::string axisLabels[6] =
	{
		"X",
		"-X",
		"Y",
		"-Y",
		"Z",
		"-Z"
	};

	unsigned int currentAxis;
	unsigned int currentAngle;

	std::vector<Quat> quatTransforms;
	std::vector<Mat4> matTransforms;

	UITextElement* currentMode;
	UITextElement* currentTransformMode;

	UITextElement* currentAxisLabel;
	UITextElement* currentAngleLabel;

	UITextElement* benchmarkTimeResult;
	UITextElement* benchmarkMemoryResult;
	UITextElement* amountOfTransformsUI;

	UITextElement* benchmarkInProgress;

	Mat4 viewMat;
	Mat4 projMat;
};