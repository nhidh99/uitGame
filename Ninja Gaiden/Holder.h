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
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY, translateX, translateY);

		if (isDropped == true)
		{
			item->Render(translateX, translateY);
		}
	}

	void Update(float dt)
	{
		curAnimation->Update(dt);
		Object::Update(dt);

		if (isDropped == true)
		{
			item->posX = this->posX;
			item->posY = this->posY + 10;
			item->Update(dt);
		}
	}
};