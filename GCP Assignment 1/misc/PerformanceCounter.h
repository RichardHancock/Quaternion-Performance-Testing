#pragma once

#include <cstdint>

//If Visual Studio
#ifdef _MSC_VER
#include <Windows.h>
#endif // _MSC_VER

class PerformanceCounter
{
	//I've decided to use Window's peformance counters as C++ chrono is not 
	// fully working in < VS 2015. and internally chrono just calls these functions anyway
public:

	static void initSubsystem();


	PerformanceCounter();

	void startCounter();

	uint64_t stopCounter();

private:

	bool running;

#ifdef _MSC_VER
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;

	/** 
	@brief	The frequency of the counter.
	Consistent value after system boot
	 */
	static LARGE_INTEGER frequency;
#endif // _MSC_VER


};