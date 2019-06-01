#pragma once
#include "Bullet.h"

class BulletCloakMan : public Bullet
{
public:

	BulletCloakMan()
	{
		activeAnimation = new Animation(BULLET, 0, 3);
		type = CLOAKMAN;
		height = BULLET_CLOAKMAN_HEIGHT;
		width = BULLET_CLOAKMAN_WIDTH;
		vy = BULLET_CLOAKMAN_JUMPING_SPEED;
		vx = BULLET_CLOAKMAN_SPEED;
	}

	void UpdateDistance(float dt)
	{
		this->vy -= GRAVITY_SPEED;
		//if (vy <= 0) vy = -BULLET_CLOAKMAN_FALLING_SPEED;
		this->dx = vx * dt;
		this->dy = vy * dt;
	}
};