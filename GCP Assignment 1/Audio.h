#pragma once

#include <SDL_mixer.h>
#include <string>

#include "Resource.h"

class Resource;

//Was used in another assignment

/**
@class Audio
@brief Abstract base class for any Audio
*/
class Audio : public Resource
{
public:

	/**
	@brief Create an Audio object.
	
	@param path Path to the audio file.
	 */
	Audio(std::string path);

	virtual ~Audio() {};
	/**
	@brief Play the stored Audio.
	
	@param ms    milliseconds of fade-in.
	@param loops How many times will this audio play (-1 for infinite , 0 to just play once)
	 */
	virtual void play(unsigned int ms, int loops) = 0;

	/**
	@brief Pause/Resume the audio
	*/
	virtual void togglePause() = 0;

	/**
	@brief Stop the stored Audio.
	
	@param ms milliseconds of fade-out.
	 */
	virtual void stop(int ms) = 0;
protected:
	/**
	@brief Loads a audio file and stores it internally
	*/
	virtual void load() = 0;

	///Path to the stored audio file
	std::string path;
};


/**
@class SFX
@brief Encapsulates a Sound Effect
*/
class SFX : public Audio
{
public:
	/**
	@brief Create an Sound Effect object
	@param path Path to the sound file
	*/
	SFX(std::string path);
	~SFX();

	/**
	@brief Play the stored Sound Effect.

	@param ms    milliseconds of fade-in.
	@param loops How many times will this SFX play (-1 for infinite , 0 to just play once)
	*/
	void play(unsigned int ms, int loops);

	/**
	@brief Pause/Resume the Sound Effect
	*/
	void togglePause();

	/**
	@brief Stop the stored Sound Effect.

	@param ms milliseconds of fade-out.
	*/
	void stop(int ms);
private:
	/**
	@brief Loads a Sound Effect file and stores it internally
	*/
	void load();

	///Currently assigned channel for the sound effect
	int channel;

	///Sound data
	Mix_Chunk* sound;
};


/**
@class Music
@brief Encapsulates music

Only one Music class can play at a time, there is no check for this so the outcome is unhandled.
*/
class Music : public Audio
{
public:

	/**
	@brief Create an Music object.

	@param path Path to the music file.
	*/
	Music(std::string path);

	~Music();

	/**
	@brief Play the stored music.

	@param ms    milliseconds of fade-in.
	@param loops How many times will this music play (-1 for infinite)
	*/
	void play(unsigned int ms, int loops);

	/**
	@brief Pause/Resume the current music track
	*/
	void togglePause();

	/**
	@brief Stop the stored music.

	@param ms milliseconds of fade-out.
	*/
	void stop(int ms);
private:
	/**
	@brief Loads a music file and stores it internally
	*/
	void load();

	///Music data
	Mix_Music* music;
};