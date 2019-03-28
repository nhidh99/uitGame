#pragma once
#include "GameGlobal.h"

struct Rect
{
	float x, y;
	float width, height;
};

struct BoundingBox
{
	float x, y;
	float width, height;
	float vx, vy;
};

struct CollisionResult
{
	bool isCollide;
	float entryTime;
	Direction dir;
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