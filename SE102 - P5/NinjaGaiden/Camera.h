#pragma once
#include "GameGlobal.h"

class Camera
{
private:
	int _width, _height;
	int _posX, _posY;
	int _vx;
	
public:
	Camera(int width, int height);
	void SetPosition(float x, float y);
	void SetPosX(float x);
	void AddPosX(float x);
	int GetWidth();
	int GetHeight();
	int GetPosX();
	int GetPosY();
	RECT GetBound();
};