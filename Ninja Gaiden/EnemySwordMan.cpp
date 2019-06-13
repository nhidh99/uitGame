#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[STANDING] = new Animation(ENEMY, 0, 0);
	animations[RUNNING] = new Animation(ENEMY, 0, 2, DEFAULT_TPF << 1);
	tag = ENEMY;
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
	speed = ENEMY_SWORDMAN_SPEED;
}

EnemySwordMan::~EnemySwordMan()
{
}

void EnemySwordMan::UpdateDistance(float dt)
{
	this->dx = vx * dt;

	if (vx > 0 && this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
	{
			this->vx = -vx;
			this->isReverse = true;
	}
	else if (vx < 0 && this->posX - (this->width >> 1) <= groundBound.x)
	{
			this->vx = -vx;
			this->isReverse = false;
	}
}
