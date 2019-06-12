#pragma once
#include "Bullet.h"

class BulletBoss : public Bullet
{
public:
	BulletBoss()
	{
		activeAnimation = new Animation(BULLET, 7, 7);
		type = BOSS;
		height = BULLET_BOSS_HEIGHT;
		width = BULLET_BOSS_WIDTH;
		vx = BULLET_BOSS_SPEED;
		vy = 0;
	}

	void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
	}
};