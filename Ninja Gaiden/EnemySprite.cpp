#include "EnemySprite.h"

EnemySprite::EnemySprite(Type type, int left, int top, int right, int bottom)
{
	this->tag = ENEMY;
	this->type = type;

	texture = TextureFactory::GetInstance()->GetTexture(tag);
	rect.top = top;
	rect.left = left;
	rect.right = right;
	rect.bottom = bottom;
	center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
}