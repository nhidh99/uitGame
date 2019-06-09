#pragma once
#include "ObjectItem.h"

class EnemyBullet : public ObjectItem
{
private:
	Sprite* sprite;
public:
	EnemyBullet();
	~EnemyBullet();
	void Update(float dt,Rect camRect);
	void Render(float translateX = 0, float translateY = 0);
	bool isOutCam(Rect camRect);
};