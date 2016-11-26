#pragma once

#include "State.h"

#include <SDL_ttf.h>

#include "../misc/Quat.h"
#include "../ui/UI.h"
#include "../misc/PerformanceCounter.h"

/** @brief	The Main State of the program. */
class MainState : public State
{
public:
	/**
	@brief Create the State.

	@param [in,out] manager		    Pointer to the current state manager.
	@param [in,out] platform	    Pointer to platform.
	*/
	MainState(StateManager* manager, Platform* platform);

	/** @brief	Destructor. */
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
	@brief Render any sprites or meshes relevant to the state
	*/
	virtual void render();

private:

	/**
	 @brief	Starts the benchmark and carries out all required logic.
	
	 @param	dt	delta time.
	 */
	void startBenchmark(float dt);

	/** @brief	Creates an array of quats. Size is the amountOfTransforms[currentAmountOfTransforms] */
	void createArrayOfQuats();

	/** @brief	Creates an array of Mat4s. Size is the amountOfTransforms[currentAmountOfTransforms] */
	void createArrayOfMats();

	/**
	 @brief	Determines rotation from Axis array and passed in angle.

	 @param	angleIn  	The angle.
	 @param	isRadians	true if the angle is in radians.
	
	 @return	A Vec4(xAxis,yAxis,zAxis,Rotation).
	 */
	Vec4 determineRotation(float angleIn, bool isRadians);

	/**
	 @brief	Creates a 3D grid of transforms rotated by the passed in transform.
	 Limited to 1000, due to render performance.

	 @param	count		   	Number of transforms (A number that can be Cube Rooted would be ideal, otherwise it's rounded up).
	 @param	rotateTransform	A rotation transform matrix.
	 */
	void createGridOfTransforms(unsigned int count, Mat4 rotateTransform);

	/** @brief	Values that represent benchmark stages. */
	enum BenchmarkStage
	{
		NotRunning, ///< Benchmark is not currently running
		Started, ///< Benchmark has been started and is in progress
		Completed ///< Benchmark has been completed
	};

	/** @brief	The font used for UI. */
	TTF_Font* font;

	/** @brief	The current radian angle for the animated mode. Can't exceed Two PI */
	float currentAnimationAngle;


	/** @brief	The shader used for 3D models. */
	Shader* modelShader;

	/** @brief	The shader for 2D UI elements. */
	Shader* uiShader;


	/** @brief	The barrel model. */
	GameModel* barrelModel;

	/** @brief	The view matrix for the camera. */
	Mat4 viewMat;

	/** @brief	The projection matrix. */
	Mat4 projMat;


	/** @brief	true to enable benchmark mode, false to use animated mode. */
	bool benchmarkMode;

	/** @brief	The curent benchmark stage. */
	BenchmarkStage benchmarkStage;

	/** @brief	true to enable quaternion mode, false for matrix mode. */
	bool quatMode;


	/** @brief	Index of the current amount of transforms. Used with amountOfTransforms array. */
	unsigned int currentAmountOfTransforms;
	/** @brief	The available options for the amount of Transforms that will be carried out. */
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

	/** @brief	Index of the current angle. Used with angles array. */
	unsigned int currentAngle;
	/** @brief	The available options for the angle (in Degrees) that will be used in the rotation. */
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

	/** @brief	Index of the current rotation axis. Used with axis array. */
	unsigned int currentAxis;
	/** @brief	The available options for the rotation axis that will be used in the rotation.*/
	const std::string axisLabels[6] =
	{
		"X",
		"-X",
		"Y",
		"-Y",
		"Z",
		"-Z"
	};


	/** @brief	Array of the quaternion transforms. */
	std::vector<Quat> quatTransforms;
	/** @brief	Array of the matrix transforms. */
	std::vector<Mat4> matTransforms;


	//UI Elements

	/** @brief	UI showing the current mode (Benchmark or Animated). */
	UITextElement* currentMode;
	/** @brief	UI showing the current transform mode (Matrix or Quaternion). */
	UITextElement* currentTransformMode;

	/** @brief	UI showing the current axis (X,X-,Y,Y-,Z,Z-). */
	UITextElement* currentAxisLabel;
	/** @brief	UI showing the current angle (10,30,45,90,180,270,360). */
	UITextElement* currentAngleLabel;

	/** @brief	UI showing the current benchmark's time result (in Milliseconds). */
	UITextElement* benchmarkTimeResult;
	/** @brief	UI showing the current benchmark's memory result (In Bytes or Killobytes). */
	UITextElement* benchmarkMemoryResult;
	/** @brief	UI showing the amount of transforms to be performed (1,10,100,1000,10000,100000,1000000). */
	UITextElement* amountOfTransformsUI;

	/** @brief	UI showing if a benchmark is in progress. */
	UITextElement* benchmarkInProgress;
};