#include "Resource.h"

#include <assert.h>
#include <climits>

Resource::Resource()
{
	instances = 1;
	keepResourceLoaded = false;
}

void Resource::freeResourceInstance()
{
	assert(instances > 0);
	instances--;
}

void Resource::loadResourceInstance()
{
	assert(instances < UINT_MAX);
	instances++;
}

unsigned int Resource::getInstanceCount()
{
	return instances;
}

bool Resource::keepLoaded()
{
	return keepResourceLoaded;
}

void Resource::keepLoaded(bool active)
{
	keepResourceLoaded = active;
}