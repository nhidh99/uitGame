#pragma once
#include "Object.h"
#include <unordered_set>

class Item : public Object
{
protected:
	float existsTime;
	Rect groundBound;
	Sprite* sprite;

public:
	Item()
	{
		this->tag = ITEM;
		this->existsTime = ITEM_EXISTS_TIME;
		this->vy = -ITEM_SPEED;
		this->width = ITEM_WIDTH;
		this->height = ITEM_HEIGHT;
	}

	void DetectGround(std::unordered_set<Rect*> grounds)
	{
		for (auto g : grounds)
		{
			Rect rect;
			rect.x = this->posX - (this->width >> 1);
			rect.y = g->y;
			rect.width = this->width;
			rect.height = this->height;

			if (rect.IsContain(*g) && g->y >= groundBound.y && this->posY - (this->height >> 1) >= g->y)
			{
				groundBound = *g;
			}
		}
	}

	void Update(float dt)
	{
		if (this->IsCollide(groundBound))
		{
			this->vy = 0;
			this->dy = 0;
		}
		else this->dy = vy * dt;

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
		sprite->Render(posX, posY + SCREEN_TRANSLATEY);
	}
};