#pragma once
#include "Item.h"
#include "Camera.h"

class Holder : public Object
{
protected:
	Animation* animation;

public:
	bool isDead;
	int itemID;

	Holder() 
	{
		this->tag = HOLDER; 
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
	}

	~Holder()
	{
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		animation->Render(posX, posY + SCREEN_TRANSLATEY);
	}

	void Update(float dt)
	{
		animation->Update(dt);
	}
};