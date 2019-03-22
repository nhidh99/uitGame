#pragma once
#include "SpriteFactory.h"
#include "Animation.h"

class Object
{
public:
	Object() {}
	Tag tag;									// Tag định loại Object
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float vx, vy;								// Vận tốc
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều dọc

	virtual void Update(float dt) {};			// Update thông số của Object sau khoảng thời gian delta-time
	virtual void Render() = 0;					// Render Object
	virtual void Render(float x, float y) {}
};