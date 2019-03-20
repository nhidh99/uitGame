#include "ObjectItemAxeSprite.h"

ObjectItemAxeSprite::ObjectItemAxeSprite(int left, int top, int right, int bottom)
{
	_tag = ITEM;
	_type = AXE;

	_rect.top = top;
	_rect.left = left;
	_rect.right = right;
	_rect.bottom = bottom;

	_width = ITEM_AXE_WIDTH;
	_height = ITEM_AXE_HEIGHT;
}

void ObjectItemAxeSprite::Render(float x, float y, float translateX, float translateY)
{
	Sprite::Render(x, y, translateX, translateY);
}