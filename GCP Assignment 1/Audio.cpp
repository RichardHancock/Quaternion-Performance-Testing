#include "Audio.h"
#include "misc/Log.h"

//Audio
Audio::Audio(std::string path)
	: Resource(), path(path)
{

}


//SFX
SFX::SFX(std::string path)
	: Audio(path), channel(0)
{
	load();
}

SFX::~SFX()
{
	Mix_FreeChunk(sound);
}

void SFX::play(unsigned int ms, int loops)
{
	int newChannel;
	newChannel = (ms <= 0 ? Mix_PlayChannel(-1, sound, loops)
		: Mix_FadeInChannel(-1, sound, loops, ms));

	if (newChannel == -1)
	{
		Log::logW("Problem trying to play sound: " + path + " Error msg: " + Mix_GetError());
	}
	else
	{
		channel = newChannel;
	}
}

void SFX::togglePause()
{
	// If Music paused resume, else pause 
	Mix_Paused(channel) ? Mix_Resume(channel) : Mix_Pause(channel);
}

void SFX::stop(int ms)
{
	//If no ms value has been given stop sound, else fade out sound.
	ms <= 0 ? Mix_HaltChannel(channel) : Mix_FadeOutChannel(channel, ms);
}

void SFX::load()
{
	sound = Mix_LoadWAV(path.c_str());
	if (sound == nullptr)
	{
		Log::logW("Sound file: " + path + " failed to load. " + Mix_GetError());
	}
}


//Music
Music::Music(std::string path)
	: Audio(path)
{
	load();
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

void Music::play(unsigned int ms, int loops)
{
	int success;
	if (!ms)
	{
		success = Mix_PlayMusic(music, loops);
	}
	else
	{
		success = Mix_FadeInMusic(music, loops, ms);
	}

	if (success < 0)
	{
		Log::logW("Problem trying to play music: " + path + " Error msg: " + Mix_GetError());
	}
}

void Music::togglePause()
{
	// If Music paused resume, else pause 
	if (Mix_PlayingMusic())
	{
		Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
	}
	else
	{
		play(0, 0);
	}

}

void Music::stop(int ms)
{
	//If no ms value has been given stop music, else fade out music.
	ms <= 0 ? Mix_HaltMusic() : Mix_FadeOutMusic(ms);
}

void Music::load()
{
	music = Mix_LoadMUS(path.c_str());
	if (music == nullptr)
	{
		Log::logW("Music file: " + path + " failed to load. " + Mix_GetError());
	}
}