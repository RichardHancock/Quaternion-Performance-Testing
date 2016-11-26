#include "UI.h"

UIElement::UIElement(Vec2 pos, Vec2 size)
	: pos(pos), size(size), backgroundTexture(nullptr)
{
	createVertices();
}

UIElement::~UIElement()
{
	if (backgroundTexture != nullptr)
	{
		backgroundTexture->freeResourceInstance();
	}
}

void UIElement::createVertices()
{
	//TODO Add scaling
	Vec2 max(pos.x + size.x, pos.y + size.y);

	std::vector<Vec3> vertices = {
		Vec3(pos.x, pos.y, 0.0f),
		Vec3(max.x, pos.y, 0.0f),
		Vec3(pos.x, max.y, 0.0f),
		Vec3(max.x, max.y, 0.0f)
	};

	std::vector<Vec2> uvs = {
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(0.0f, 1.0f),
		Vec2(1.0f, 1.0f)
	};

	std::vector<unsigned int> indices = {
		0, 2, 1,
		1, 2, 3
	};

	renderable = new GameModel(&vertices, nullptr, &uvs, &indices, nullptr);
}

void UIElement::addTexture(Texture* newTexture, std::string shaderVarName)
{
	this->backgroundTexture = newTexture;
	renderable->addTexture(newTexture, shaderVarName);
}

void UIElement::draw(Shader* shader)
{
	if (renderable != nullptr)
	{
		renderable->draw2D(shader);
	}
}


UITextElement::UITextElement(Vec2 pos, Vec2 size, std::string text, Colour fgColour, TTF_Font* font)
	: UIElement(pos, size), displayedText(text), foregroundColour(fgColour), font(font), mergedTexture(nullptr)
{
	textureRequiresMerge = true;
}

void UITextElement::changeText(std::string text)
{
	textureRequiresMerge = true;
	displayedText = text;

	
}

void UITextElement::draw(Shader* shader)
{
	if (textureRequiresMerge)
	{
		updateMergedTexture();
	}

	if (renderable != nullptr)
	{
		renderable->draw2D(shader);
	}
}

void UITextElement::updateMergedTexture()
{
	renderable->deleteTexturesFromGPU();

	Texture* textSurface = new Texture(TTF_RenderText_Blended(font, displayedText.c_str(), foregroundColour.convertToSDLColour()));

	if (backgroundTexture != nullptr)
	{
		if (mergedTexture != nullptr)
		{
			delete mergedTexture;
			mergedTexture = nullptr;
		}

		mergedTexture = backgroundTexture->copy();
	}
	else
	{
		if (mergedTexture != nullptr)
		{
			delete mergedTexture;
			mergedTexture = nullptr;
		}

		mergedTexture = textSurface->copy();
		renderable->addTexture(mergedTexture, "gSampler");
		delete textSurface;
		textSurface = nullptr;
		textureRequiresMerge = false;
		return;
	}

	Vec2 textDimensions = textSurface->getDimensions();
	Vec2 dstDimensions = mergedTexture->getDimensions();

	//Need to center text
	Vec2 margin = (dstDimensions - textDimensions) / 2;

	SDL_Rect rect;
	rect.x = (int) margin.x;
	rect.y = (int) margin.y;
	rect.w = (int) textDimensions.x;
	rect.h = (int) textDimensions.y;

	SDL_BlitSurface(textSurface->getRawSurface(), NULL,
		mergedTexture->getRawSurface(), &rect);

	renderable->addTexture(mergedTexture, "gSampler");
	
	delete textSurface;
	textSurface = nullptr;
	textureRequiresMerge = false;
}
