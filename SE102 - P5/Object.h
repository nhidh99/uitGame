#pragma once
#include "SpriteFactory.h"
#include "Animation.h"
#include "Collision.h"

class Object
{
public:
	Object() {}
	Tag tag;									// Tag định loại Object
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều dọc

	RECT GetBound()
	{
		RECT bound;
		bound.left = posX - (width >> 1);
		bound.right = bound.left + width;
		bound.top = posY - (height >> 1);
		bound.bottom = bound.top + height;
		return bound;
	}

	BoundingBox GetBoundingBox()
	{
		BoundingBox bound;
		bound.height = height;
		bound.width = width;
		bound.x = posX - (width >> 1);
		bound.y = posY - (height >> 1);
		bound.vx = dx;
		bound.vy = dy;
		return bound;
	}

	virtual void Update(float dt) 
	{
		dx = vx * dt;
		dy = vy * dt;
		posX += dx;
		posY += dy;
	};			// Update thông số của Object sau khoảng thời gian delta-time
	virtual void Render() {}
	virtual void Render(float translateX = 0, float translateY = 0) {}
};