#pragma once
#include "Sprite.h"

class BulletSprite : public Sprite
{
public:
	Type type;
	BulletSprite() {};
	
	BulletSprite(Type type, int left, int top, int right, int bottom)
	{
		this->tag = BULLET;
		this->type = type;

		texture = TextureFactory::GetInstance()->GetTexture(tag);
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;
		center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};