#pragma once
#include "Bullet.h"

class BulletGunMan : public Bullet
{
public:	
	BulletGunMan()
	{
		activeAnimation = new Animation(BULLET, 4, 4);
		type = GUNMAN;
		height = BULLET_GUNMAN_HEIGHT;
		width = BULLET_GUNMAN_WIDTH;
		vx = BULLET_GUNMAN_SPEED;
	}

	void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
	}
};