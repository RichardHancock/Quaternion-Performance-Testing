#pragma once

#include <string>

#include "../misc/Vec2.h"
#include "../misc/Colour.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../GameModel.h"

class UIElement
{
public:
	UIElement(Vec2 pos, Vec2 size);

	~UIElement();

	void addTexture(Texture* newTexture, std::string shaderVarName);

	void draw(Shader* shader);

protected:
	Vec2 pos;

	Vec2 size;

	Texture* backgroundTexture;

	GameModel* renderable;

	void createVertices();

};


class UITextElement : public UIElement
{
public:
	UITextElement(Vec2 pos, Vec2 size, std::string text, Colour fgColour, TTF_Font* font);

	void changeText(std::string text);

	void draw(Shader* shader);

protected:
	void updateMergedTexture();

	bool textureRequiresMerge;

	Texture* mergedTexture;

	std::string displayedText;

	Colour foregroundColour;

	TTF_Font* font;
};


class UIManager
{
public:

	bool isClicked(std::string elementName, Vec2 mousePos);
private:

};
