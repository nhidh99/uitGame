#pragma once
#include "Game.h"

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
};