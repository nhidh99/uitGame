#pragma once
#include "Item.h"
#include "Camera.h"

class Holder : public Object
{
protected:
	Animation* curAnimation;

public:
	bool isDead;
	int itemID;
	Type type;

	Holder() 
	{
		this->tag = HOLDER; 
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
	}
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