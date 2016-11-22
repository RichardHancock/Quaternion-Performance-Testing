#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "misc/Vec2.h"
#include "Resource.h"

#pragma once

//Used in other assignments, small modifications

/**
@class Texture
@brief Encapsulates an SDL_Texture

Contains the ability to draw, load, etc.. Textures.
*/
class Texture : public Resource
{
public:
	/**
	@brief Create a Texture
	@param path Path to image
	*/
	Texture(std::string path);

	/**
	@brief Create a Texture
	@param surface A surface to convert into a texture (This is freed internally)
	*/
	Texture(SDL_Surface* surface);

	~Texture();

	/**
	@brief Gets the Dimensions of the stored texture
	@return Vec2 - Dimensions of Sprite
	*/
	Vec2 getDimensions();


	/**
	@brief Load Image
	@param path Path to image
	*/
	bool load(std::string path);

	/**
	@brief Load Image
	@param image A surface to convert into a texture (This is freed internally)
	*/
	bool load(SDL_Surface* image);

	/**
	@brief Copies this Texture.
	
	@return null if it fails, else a SDL_Surface*.
	 */
	Texture* copy();

	/**
	 @brief Gets raw surface.
	
	 @return null if it fails, else the raw surface.
	 */
	SDL_Surface* getRawSurface() { return surface; }
private:

	/** @brief The surface. */
	SDL_Surface* surface;
};

