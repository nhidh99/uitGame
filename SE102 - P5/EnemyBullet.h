#pragma once
#include "ObjectItem.h"


class EnemyBullet : public ObjectItem
{
private:
	Sprite* sprite;
public:
	EnemyBullet();
	~EnemyBullet();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};