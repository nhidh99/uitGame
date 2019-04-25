#pragma once
#include "ObjectItem.h"

class ObjectItemShuriken : public ObjectItem
{
private:
	Sprite *_sprite;

public:
	ObjectItemShuriken();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};