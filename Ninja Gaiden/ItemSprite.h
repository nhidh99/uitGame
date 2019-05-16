#pragma once
#include "Sprite.h"

class ItemSprite : public Sprite
{
public:
	Type type;
	ItemSprite() {};
	ItemSprite(Type type, int left, int top, int right, int bottom)
	{
		this->tag = ITEM;
		this->type = type;

		_texture = TextureFactory::GetInstance()->GetTexture(tag);
		_rect.top = top;
		_rect.left = left;
		_rect.right = right;
		_rect.bottom = bottom;
		_center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};