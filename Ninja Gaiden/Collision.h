#pragma once
#include "GameGlobal.h"

struct BoundingBox
{
	float x, y;
	float width, height;
	float vx, vy;

	BoundingBox() {}
	~BoundingBox() {}

	BoundingBox(float x, float y, float w, float h, float vx = 0, float vy = 0)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		this->vx = vx;
		this->vy = vy;
	}
};

struct CollisionResult
{
	bool isCollide;
	float entryTime;
	int nx, ny;
};

class Collision
{
private:
	float dxEntry, dxExit;
	float dyEntry, dyExit;
	float txEntry, tyEntry;
	float txExit, tyExit;
	float entryTime;
	float exitTime;

	static Collision* instance;

public:
	static Collision* GetInstance();
	bool IsCollision(BoundingBox b1, BoundingBox b2);
	CollisionResult SweptAABB(BoundingBox b1, BoundingBox b2);
};