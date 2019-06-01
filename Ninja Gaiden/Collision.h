#pragma once
#include "GameGlobal.h"

struct BoundingBox
{
	float top, left, right, bottom;
	float vx, vy;

	BoundingBox() {}
	~BoundingBox() {}
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