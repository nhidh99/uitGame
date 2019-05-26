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
	virtual ~Object() {}

	Tag tag;									// Tag định loại Object
	Type type;
	float spawnX, spawnY;
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều ngang
	bool isDead;

	Rect GetRect();
	BoundingBox GetBoundingBox();

	void Update(float dt);
	bool IsCollide(Rect r);
	virtual void Render(float translateX = 0, float translateY = 0) {}
};