#include "Colour.h"


//Colour
Colour::Colour()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

Colour::Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Colour::Colour(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Colour::Colour(uint8_t rgb)
{
	this->r = rgb;
	this->g = rgb;
	this->b = rgb;
	this->a = 255;
}

Colour::Colour(Vec3 colour)
{
	this->r = (uint8_t)colour.x;
	this->g = (uint8_t)colour.y;
	this->b = (uint8_t)colour.z;
	this->a = 255;
}


SDL_Colour Colour::convertToSDLColour()
{
	SDL_Colour newColour;
	newColour.r = this->r;
	newColour.g = this->g;
	newColour.b = this->b;
	newColour.a = this->a;
	return newColour;
}