#pragma once
#include "Object.h"

class Holder : public Object
{
protected:
	Animation* curAnimation;
	Sprite* item;
	Type type;

public:
	Holder() { tag = HOLDER; }
	~Holder() {};

	void Render(float translateX = 0, float translateY = 0)
	{
		curAnimation->Render(posX, posY, translateX, translateY);
	}

	void Update(float dt)
	{
		curAnimation->Update(dt);
	}
};