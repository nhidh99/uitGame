#pragma once
#include "ObjectItem.h"

class ObjectItemShuriken : public ObjectItem
{
public:
	ObjectItemShuriken();
	void SetPosition(float x, float y);
	void Update(float dt);
	void Render();
};