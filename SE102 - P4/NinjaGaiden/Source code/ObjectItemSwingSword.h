#pragma once
#include "ObjectItem.h"

class ObjectItemSwingSword : public ObjectItem
{
public:
	ObjectItemSwingSword();
	void Update(float dt);
	void Render(float x, float y, int frameIndex);
};