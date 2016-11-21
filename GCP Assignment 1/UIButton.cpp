#include "UIButton.h"

#include "input/InputManager.h"

UIButton::UIButton(Vec2 pos, Texture* texture)
	: texture(texture), pos(pos)
{
	AABB.x = (int)pos.x;
	AABB.y = (int)pos.y;
	AABB.h = (int)texture->getDimensions().y;
	AABB.w = (int)texture->getDimensions().x;
}

UIButton::~UIButton()
{
	texture->freeResourceInstance();
}

void UIButton::update(float dt)
{

}

bool UIButton::isClicked()
{
	SDL_Rect mouse;
	mouse.x = (int)InputManager::getMousePos().x;
	mouse.y = (int)InputManager::getMousePos().y;
	mouse.h = mouse.w = 1;
	
	return SDL_HasIntersection(&mouse, &AABB) == SDL_TRUE;
}

void UIButton::render(Vec2 scale)
{
	texture->drawScaled(pos, scale);
}

SDL_Rect UIButton::getAABB()
{
	return AABB;
}
