#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[STANDING] = new Animation(ENEMY, 0, 0);
	animations[ATTACKING] = new Animation(ENEMY, 0, 2);
	tag = ENEMY;
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;

	srand(time(NULL));
	int x = rand();
	if (x & 1)
	{
		this->isReverse = false;
		vx = ENEMY_SWORDMAN_SPEED;
		distance = rand() % 200 + 100;
	}
	else
	{
		this->isReverse = true;
		vx = -ENEMY_SWORDMAN_SPEED;
		distance = -(rand() % 200 + 100);
	}
}

EnemySwordMan::~EnemySwordMan()
{
}

void EnemySwordMan::UpdateDistance(float dt)
{
	this->dx = vx * dt;
	this->distance -= dx;

	if (vx > 0)
	{
		if (distance <= 0 || this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
		{
			distance = -(rand() % 200 + 100);
			this->vx = -vx;
			this->isReverse = true;
		}
	}
	else
	{
		if (distance >= 0 || this->posX - (this->width >> 1) <= groundBound.x)
		{
			distance = (rand() % 200 + 100);
			this->vx = -vx;
			this->isReverse = false;
		}
	}
}
