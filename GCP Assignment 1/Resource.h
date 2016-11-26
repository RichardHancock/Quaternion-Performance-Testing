#pragma once

//Was used in another assignment

/** @brief	A base class for a resource type. */
class Resource
{
public:
	/** @brief	Default constructor. */
	Resource();

	/** 
	@brief	Free a resource instance.
	Decrements instance count
	*/
	void freeResourceInstance();
	
	/** 
	@brief	Loads a resource instance. 
	Increments instance count
	*/
	void loadResourceInstance();

	/**
	 @brief	Gets current instance count.
	
	 @return	The instance count.
	 */
	unsigned int getInstanceCount();

	/**
	 @brief	Checks if this resource is set to stay loaded.
	
	 @return	true if it will stay loaded.
	 */
	bool keepLoaded();

	/**
	 @brief	Set this resource to keep loaded even if none are currently in use.
	
	 @param	active	true to keep loaded.
	 */
	void keepLoaded(bool active);

protected:

	/** @brief	The current instance count. */
	unsigned int instances;

	/** @brief	true if keeping resource loaded. */
	bool keepResourceLoaded;
};