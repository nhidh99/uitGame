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

	Rect GetRect()
	{
		Rect rect;
		rect.x = posX - (width >> 1);
		rect.y = posY - (height >> 1);
		rect.width = width;
		rect.height = height;
		return rect;
	}
};