#pragma once
#include "SpriteFactory.h"
#include "Animation.h"
#include "Collision.h"

class Object;

class Cell
{
	int xID, yID;

public:
	Rect rect;
	static int width, height;
	std::vector<Object*> objects;

	Cell(int xID, int yID);
	bool IsContain(Rect r);
	void Update(std::vector<Object*> objs);
};

class Object
{
public:
	Object() {}
	Tag tag;									// Tag định loại Object
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều ngang

	Rect GetRect()
	{
		Rect rect;
		rect.x = posX - (width >> 1);
		rect.y = posY - (height >> 1);
		rect.width = this->width;
		rect.height = this->height;
		return rect;
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

	virtual void Update(float dt)  // Update thông số của Object sau khoảng thời gian delta-time
	{
		dx = vx * dt;
		dy = vy * dt;
		posX += dx;
		posY += dy;
	};

	virtual void Render() {}
	virtual void Render(float translateX = 0, float translateY = 0) {}
};