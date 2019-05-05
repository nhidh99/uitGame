#pragma once
#include "Player.h"

class Camera
{
private:
	static Camera* instance;

public:
	int width, height;
	float posX, posY;
	static Camera* GetInstance();

	Camera();
	Rect GetRect();
	void Update(Rect MapRect);
};