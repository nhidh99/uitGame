#pragma once
#include "ObjectItem.h"

class ObjectItemSword : public ObjectItem
{
private:
	Animation *_animation;

public:
	ObjectItemSword();
	void Update(float dt);
	void Render(float x, float y, int frameIndex, float translateX = 0, float translateY = 0);
};