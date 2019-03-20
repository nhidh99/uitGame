#include "Ball.h"

// Update Ball, cụ thể ở đây là tọa độ
void CBall::Update(DWORD dt)
{
	// Tốc độ
	x += vx * dt;
	y += vy * dt;
}

// Render Ball theo tùng state
void CBall::Render()
{
	animation->Render(x, y);
}

void CBall::AddPosX(int x)
{
	this->x += x;
}

