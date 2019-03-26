#pragma once
#include "GameGlobal.h"

struct BoundingBox
{
	float x, y;
	int width, height;
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
	int dxEntry, dxExit;
	int dyEntry, dyExit;

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