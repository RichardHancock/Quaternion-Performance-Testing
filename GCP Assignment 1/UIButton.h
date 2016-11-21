#pragma once

#include <SDL.h>

#include "Texture.h"
#include "misc/Vec2.h"

class UIButton
{
public:

	UIButton(Vec2 pos, Texture* texture);

	~UIButton();

	void update(float dt);

	bool isClicked();

	void render(Vec2 scale);

	SDL_Rect getAABB();
private:

	Vec2 pos;

	SDL_Rect AABB;

	Texture* texture;
};