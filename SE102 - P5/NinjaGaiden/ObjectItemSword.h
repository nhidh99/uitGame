#pragma once
#include "ObjectItem.h"

class ObjectItemSword : public ObjectItem
{
public:
	ObjectItemSword();
	void Update(float dt);
	void Render(float x, float y, int frameIndex);
};