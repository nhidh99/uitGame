#pragma once
#include "Object.h"
#include "Camera.h"

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
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;

		camera->ConvertPositionToViewPort(posX, posY);
		curAnimation->Render(posX, posY);
	}

	void Update(float dt)
	{
		curAnimation->Update(dt);
	}
};