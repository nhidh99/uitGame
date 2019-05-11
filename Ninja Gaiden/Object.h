#pragma once
#include "GameGlobal.h"
#include "SpriteFactory.h"
#include "Animation.h"
#include "Collision.h"
#include "Camera.h"

class Object
{
public:
	Object() {}
	~Object() {}

	Tag tag;									// Tag định loại Object
	float spawnX, spawnY;
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều ngang

	Rect GetRect();
	BoundingBox GetBoundingBox();

	void Update(float dt);
	bool IsCollide(Rect r);
	virtual void Render(float translateX = 0, float translateY = 0) {}
};