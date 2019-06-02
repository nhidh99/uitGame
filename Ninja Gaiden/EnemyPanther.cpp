#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[STANDING] = new Animation(ENEMY, 15, 15);
	animations[RUNNING] = new Animation(ENEMY, 15, 16);
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
	speed = 0.14f;
}

EnemyPanther::~EnemyPanther()
{
}

void EnemyPanther::UpdateDistance(float dt)
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
