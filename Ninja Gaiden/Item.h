#pragma once
#include "Object.h"
#include <unordered_set>

class Item : public Object
{
protected:
	float existsTime;
	Rect groundBound;

public:
	bool isDead;
	float groundY;
	Type type;
	Sprite* sprite;

	Item()
	{
		this->tag = ITEM;
		this->existsTime = ITEM_EXISTS_TIME;
		this->vy = -ITEM_SPEED;
		this->width = ITEM_WIDTH;
		this->height = ITEM_HEIGHT;
	}

	void DectectGround(std::unordered_set<Rect*> grounds)
	{
		for (auto g : grounds)
		{
			if (g->x < this->posX && this->posX < g->x + g->width && g->y >= groundBound.y)
			{
				groundBound = *g;
			}
		}
	}

	void Update(float dt)
	{
		dy = vy * dt;

		if (this->IsCollide(groundBound))
		{
			vy = 0;
		}

		existsTime -= dt;
		if (existsTime <= 0)
		{
			this->isDead = true;
		}
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->Render(posX, posY);
	}
};