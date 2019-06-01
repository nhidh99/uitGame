#include "EnemyRunMan.h"

EnemyRunMan::EnemyRunMan()
{
	animations[STANDING] = new Animation(ENEMY, 5, 5);
	animations[RUNNING] = new Animation(ENEMY, 5, 6);
	type = RUNMAN;
	height = ENEMY_RUNMAN_HEIGHT;
	width = ENEMY_RUNMAN_WIDTH;
	speed = ENEMY_RUNMAN_SPEED;
}

void EnemyRunMan::UpdateDistance(float dt)
{
	this->dx = vx * dt;

	if (this->vx > 0 && this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
	{
		this->isReverse = true;
		this->vx = -vx;
	}
	else if (this->vx < 0 && this->posX - (this->width >> 1) <= groundBound.x)
	{
		this->isReverse = false;
		this->vx = -vx;
	}
}