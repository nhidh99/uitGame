#pragma once
#include "GameGlobal.h"

class Camera
{
public:
	int width, height;
	float posX, posY;
	
	Camera(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	RECT GetBound()
	{
		RECT bound;
		bound.left = posX - (width >> 1);
		bound.right = bound.left + width;
		bound.top = posY - (height >> 1);
		bound.bottom = bound.top + height;
		return bound;
	}
};