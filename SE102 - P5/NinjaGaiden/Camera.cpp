#include "Camera.h"

Camera::Camera(int width, int height)
{
	_width = width;
	_height = height;
	_posX = _posY = 0;
	_vx = 0;
}

void Camera::SetPosition(float x, float y)
{
	_posX = x;
	_posY = y;
}

void Camera::SetPosX(float x)
{
	_posX = x;
}

void Camera::AddPosX(float x)
{
	_posX += x;
}

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}

int Camera::GetPosX()
{
	return _posX;
}

int Camera::GetPosY()
{
	return _posY;
}

RECT Camera::GetBound()
{
	RECT bound;
	bound.left = _posX - (_width >> 1);
	bound.right = bound.left + _width;
	bound.top = _posY - (_height >> 1);
	bound.bottom = bound.top + _height;
	return bound;
}
