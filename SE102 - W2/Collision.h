#pragma once
#include<WinUser.h>
#include<d3d9.h>
#include"d3dx9.h"
#include"dinput.h"


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

	static Collision* _instance;

public:
	static Collision* Get_instance();
	bool IsCollision(BoundingBox b1, BoundingBox b2);
	CollisionResult SweptAABB(BoundingBox b1, BoundingBox b2);
	bool SweptGround(BoundingBox b1, BoundingBox b2);
};