#include "Camera.h"

Camera* Camera::instance = NULL;

Camera* Camera::GetInstance()
{
	if (instance == NULL)
		instance = new Camera();
	return instance;
}

Camera::Camera()
{
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}

Rect Camera::GetRect()
{
	Rect bound;
	bound.x = posX - (width >> 1);
	bound.y = posY - (height >> 1);
	bound.width = this->width;
	bound.height = this->height;
	return bound;
}

void Camera::Update(Rect MapRect)
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
