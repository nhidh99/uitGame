#pragma once
#pragma once
#include"Sprite.h"

class HolderSprite : public Sprite
{
public:
	Type type;
	HolderSprite() {};
	HolderSprite(Type type, int left, int top, int right, int bottom);
};