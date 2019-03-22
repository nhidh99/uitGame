#pragma once
#include "ObjectItemSprite.h"

class ObjectItemAxeSprite : public ObjectItemSprite
{
public:
	ObjectItemAxeSprite(int left, int top, int right, int bottom);
	void Render(float x, float y, float translateX = 0, float translateY = 0);
};