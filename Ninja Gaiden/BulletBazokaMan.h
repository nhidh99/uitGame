#pragma once
#include "Bullet.h"

class BulletBazokaMan : public Bullet
{
public:
	BulletBazokaMan()
	{
		activeAnimation = new Animation(BULLET, 6, 6);
		type = BAZOKAMAN;
		height = BULLET_BAZOKAMAN_HEIGHT;
		width = BULLET_BAZOKAMAN_WIDTH;
		vx = BULLET_BAZOKAMAN_SPEED;
		vy = 0;
	}

	void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
	}
};