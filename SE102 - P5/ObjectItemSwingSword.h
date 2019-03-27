#pragma once
#include "ObjectItem.h"

class ObjectItemSwingSword : public ObjectItem
{
private:
	Animation *_animation;

public:
	ObjectItemSwingSword();
	void Update(float dt);
	void Render(float x, float y, int frameIndex, float translateX, float translateY);
};