#pragma once
#include "Object.h"
#include "HolderItem.h"

class Holder : public Object
{
protected:
	Animation* curAnimation;
public:
	Holder() { tag = HOLDER; }
	~Holder() {};
	Type type;
	HolderItem* item;
	bool isDropped;

	void Render()
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

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