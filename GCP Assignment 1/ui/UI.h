#pragma once

#include <string>

#include "../misc/Vec2.h"
#include "../misc/Colour.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../GameModel.h"

//Modified but a previous version was used in another assignment

/** @brief	A Basic UI element that displays a texture. */
class UIElement
{
public:

	/**
	 @brief	Constructor.
	
	 @param	pos 	The position.
	 @param	size	The size.
	 */
	UIElement(Vec2 pos, Vec2 size);

	/** @brief	Destructor. */
	~UIElement();

	/**
	 @brief	Adds a texture to 'shaderVarName'.
	
	 @param [in,out]	newTexture	If non-null, the new texture data.
	 @param	shaderVarName		  	Name of the shader variable.
	 */
	void addTexture(Texture* newTexture, std::string shaderVarName);

	/**
	 @brief	Draws the UI Element using the given shader.
	
	 @param [in,out]	shader	If non-null, the shader.
	 */
	void draw(Shader* shader);

protected:
	/** @brief	The position. */
	Vec2 pos;

	/** @brief	The size. */
	Vec2 size;

	/** @brief	The background texture of the UI Element. */
	Texture* backgroundTexture;

	/** @brief	The flat plane the texture is rendered onto. */
	GameModel* renderable;

	/** @brief	Creates the flat plane with the given dimensions to render the texure onto. */
	void createVertices();

};


/** @brief	A UI element that supports rendering text using SDL2_ttf. */
class UITextElement : public UIElement
{
public:

	/**
	 @brief	Constructor.
	
	 @param	pos					The position.
	 @param	size				The size.
	 @param	text				The text to display.
	 @param	fgColour			The foreground colour of the text.
	 @param [in,out]	font	If non-null, the font.
	 */
	UITextElement(Vec2 pos, Vec2 size, std::string text, Colour fgColour, TTF_Font* font);

	/**
	 @brief	Change displayed text.
	
	 @param	text	The text.
	 */
	void changeText(std::string text);

	/**
	 @brief	Draws the UI Element using the given shader.

	 @param [in,out]	shader	If non-null, the shader.
	 */
	void draw(Shader* shader);

protected:
	/** @brief	Merges the Text's texture and the background texture(if exists). */
	void updateMergedTexture();

	/** @brief	true if the texture requires a re-merge. */
	bool textureRequiresMerge;

	/** @brief	The merged texture rendered onto the flat plane. */
	Texture* mergedTexture;

	/** @brief	The displayed text. */
	std::string displayedText;

	/** @brief	The foreground colour of the text. */
	Colour foregroundColour;

	/** @brief	The font. */
	TTF_Font* font;
};