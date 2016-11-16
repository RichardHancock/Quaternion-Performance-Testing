#pragma once

class Resource
{
public:
	Resource();

	void freeResourceInstance();
	void loadResourceInstance();

	unsigned int getInstanceCount();

	bool keepLoaded();
	void keepLoaded(bool active);

protected:
	unsigned int instances;
	bool keepResourceLoaded;
};