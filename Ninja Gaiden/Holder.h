#pragma once
#include "Object.h"

class Holder : public Object
{
protected:
	Animation* curAnimation;
	Sprite* item;
public:
	Holder() { tag = HOLDER; }
	~Holder() {}; 
	Type type;

	void Render()
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY, translateX, translateY);
	}

	void Update(float dt)
	{
		curAnimation->Update(dt);
		Object::Update(dt);
	}
};