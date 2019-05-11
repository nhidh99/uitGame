#pragma once
#include "Object.h"

class HolderItem : public Object
{
public:
	Type type;
	Sprite* sprite;
	bool isOnScreen;

	HolderItem() 
	{ 
		this->tag = ITEM;
		this->isOnScreen = false;
	};
	~HolderItem() {} ;

	void Update(float dt)
	{
		this->posX += dt * vx;
		this->posY += dt * vy;

		if (this->posY >= 119)
		{
			this->posY = 119;
		}
	}
	void Render(float translateX, float translateY)
	{
		if (this->isOnScreen)
		{
			sprite->Render(posX, posY + 5, translateX, translateY);
		}
	}
};