#include "MemoryCounter.h"


#include <windows.h>
#include <psapi.h>

float MemoryCounter::getMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS pmc;
	int result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	return (pmc.PagefileUsage / 1024.0f / 1024.0f);
}
