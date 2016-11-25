#include "MemoryCounter.h"


#include <windows.h>
#include <psapi.h>

long long MemoryCounter::getMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS pmc;
	int result = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	return (pmc.PagefileUsage);
}
