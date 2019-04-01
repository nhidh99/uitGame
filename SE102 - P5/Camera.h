#pragma once
#include "GameGlobal.h"
#include "Collision.h"

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
};