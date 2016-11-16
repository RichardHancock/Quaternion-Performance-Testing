#include "ResourceManager.h"
#include "Audio.h"
#include "misc/Log.h"

//Static Declarations
const std::string ResourceManager::audioDir = "resources/audio/";
const std::string ResourceManager::textureDir = "resources/textures/";
const float ResourceManager::UPDATE_DELAY = 10.0f;
std::unordered_map<std::string, Audio*> ResourceManager::audio;
std::unordered_map<std::string, Texture*> ResourceManager::textures;

Utility::SimpleTimer ResourceManager::updateDelayTimer(UPDATE_DELAY);
SDL_Renderer* ResourceManager::renderer = nullptr;

SDL_Renderer * ResourceManager::getRenderer()
{
	return renderer;
}

void ResourceManager::setRenderer(SDL_Renderer* newRenderer)
{
	ResourceManager::renderer = newRenderer;
}

void ResourceManager::cleanup()
{
	for (auto curAudio : audio)
	{
		if (curAudio.second != nullptr)
			delete curAudio.second;
	}
	audio.clear();

	for (auto texture : textures)
	{
		if (texture.second != nullptr)
			delete texture.second;
	}
	textures.clear();
}

Audio* ResourceManager::getAudio(std::string audioFilename, bool isMusic, bool defaultPath)
{
	//Should we use the default path for this type of resource or just use the provided filename
	if (defaultPath) {
		audioFilename = audioDir + audioFilename;
	}
	
	//Is it already loaded
	if (audio.count(audioFilename) > 0)
	{
		//Get a instance of the resource and increment its internal counter
		audio[audioFilename]->loadResourceInstance();
		return audio[audioFilename];
	}

	//Else load the resource and add it to the resourceManager's storage
	Audio* audioFile;
			
	if (isMusic)
	{
		audioFile = new Music(audioFilename);
	}
	else
	{
		audioFile = new SFX(audioFilename);
	}

	audio[audioFilename] = audioFile;
	
	return audioFile;
}

Texture* ResourceManager::getTexture(std::string textureFilename, bool defaultPath)
{
	//Should we use the default path for this type of resource or just use the provided filename
	if (defaultPath) {
		textureFilename = textureDir + textureFilename;
	}

	//Is it already loaded
	if (textures.count(textureFilename) > 0)
	{
		//Get a instance of the resource and increment its internal counter
		textures[textureFilename]->loadResourceInstance();
		return textures[textureFilename];
	}

	//Else load the resource and add it to the resourceManager's storage
	Texture* textureData = new Texture(textureFilename, renderer);

	textures[textureFilename] = textureData;

	return textureData;
}

void ResourceManager::update(float dt)
{
	//I use a timer here so the code is only run occasionally
	updateDelayTimer.update(dt);
	
	if (updateDelayTimer.hasTimerFinished())
	{
		checkForExpiredResources(audio);
		checkForExpiredResources(textures);

		updateDelayTimer.restart();
	}
}

template<class R>
void ResourceManager::checkForExpiredResources(std::unordered_map<std::string, R> &resourceArray)
{
	//Loop through the resource array
	for (auto it = resourceArray.begin(); it != resourceArray.end(); )
	{
		//If the resource isn't being used and isn't flagged to stay loaded
		if (it->second->getInstanceCount() == 0 &&
			!it->second->keepLoaded())
		{
			//Delete from the resource array
			it = resourceArray.erase(it);
		}
		else 
		{
			it++;
		}
	}
}