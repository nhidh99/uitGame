#pragma once
#include "Player.h"

class Camera
{
public:
	int width, height;
	float posX, posY;

	Camera(float width, float height)
	{
		this->width = width;
		this->height = height;
	}

	RECT GetBound()
	{
		RECT bound;
		bound.left = posX - (width / 2);
		bound.right = bound.left + width;
		bound.top = posY - (height / 2);
		bound.bottom = bound.top + height;
		return bound;
	}

	Rect GetRect()
	{
		Rect bound;
		bound.x = posX - (width >> 1);
		bound.y = posY - (height >> 1);
		bound.width = this->width;
		bound.height = this->height;
		return bound;
	}

	BoundingBox GetBoundingBox()
	{
		BoundingBox bound;
		bound.x = posX - (width / 2);
		bound.y = posY - (height / 2);
		bound.width = this->width;
		bound.height = this->height;
		bound.vx = bound.vy = 0;
		return bound;
	}

	void Update(Rect MapRect)
	{
		this->posX = player->posX;

		// Camera về phần trái của map
		if (this->posX <= this->width >> 1)
		{
			this->posX = this->width >> 1;
			player->posX = max(player->width >> 1, player->posX);
		}

		// Camera về phần phải của map
		else if (this->posX >= MapRect.width - (this->width >> 1))
		{
			this->posX = MapRect.width - (this->width >> 1);
			player->posX = min(MapRect.width - player->width, player->posX);
		}
	}
};