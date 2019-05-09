#pragma once
#include "GameGlobal.h"

class Camera
{
private:
	static Camera* instance;

public:
	float x, y;
	int width, height;

	static Camera* GetInstance();
	Camera();
	Rect GetRect();
	void Update(Rect MapRect);
	void ConvertPositionToViewPort(float& x, float& y);
};