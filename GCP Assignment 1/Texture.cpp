#include "Texture.h"

#include <iostream>
#include <assert.h>

#include "misc/Log.h"

Texture::Texture(std::string filename)
	: Resource()
{	
	load(filename);
}

Texture::Texture(SDL_Surface* surface)
	: Resource()
{
	load(surface);
}

Texture::~Texture()
{
	SDL_FreeSurface(surface);
}

bool Texture::load(std::string filename)
{
	surface = IMG_Load(filename.c_str());
	if (!surface)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		Log::logW("Can't find image named " + filename + " " + std::string(IMG_GetError()));
		return false;
	}

	return true;
}

bool Texture::load(SDL_Surface* image)
{
	surface = image;
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		Log::logW("Image passed to Texture::load was null: " + std::string(IMG_GetError()));
		return false;
	}

	return true;
}

Texture* Texture::copy()
{
	SDL_PixelFormat* format = surface->format;

	SDL_Surface* tempSurface = SDL_CreateRGBSurface(
		0,
		surface->w,
		surface->h,
		format->BitsPerPixel,
		format->Rmask,
		format->Gmask,
		format->Bmask,
		format->Amask
		);
	
	assert(tempSurface != nullptr);

	//TODO: maybe should set blend modes to none

	SDL_BlitSurface(surface, NULL, tempSurface, NULL);

	return new Texture(tempSurface);
}


Vec2 Texture::getDimensions()
{
	return (surface != nullptr ? Vec2((float) surface->w, (float) surface->h) : Vec2(0.0f));
}
