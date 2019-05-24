#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[STANDING] = new Animation(ENEMY, 12, 12);
	animations[ATTACKING] = new Animation(ENEMY, 12, 14);
	tag = ENEMY;
	type = CLOAKMAN;
	height = ENEMY_CLOAKMAN_HEIGHT;
	width = ENEMY_CLOAKMAN_WIDTH;

	srand(time(NULL));
	int x = rand();
	if (x & 1)
	{
		vx = ENEMY_SWORDMAN_SPEED;
		distance = rand() % 50 + 50;
	}
	else
	{
		vx = -ENEMY_SWORDMAN_SPEED;
		distance = -(rand() % 50 + 50);
	}
}

EnemyCloakMan::~EnemyCloakMan()
{
}

void EnemyCloakMan::UpdateDistance(float dt)
{
	this->dx = vx * dt;
	this->distance -= dx;
	this->isReverse = (player->posX < this->posX);

	if (vx > 0)
	{
		if (distance <= 0 || this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
		{
			distance = -(rand() % 50 + 50);
			this->vx = -vx;
		}
	}
	else
	{
		if (distance >= 0 || this->posX - (this->width >> 1) <= groundBound.x)
		{
			distance = (rand() % 50 + 50);
			this->vx = -vx;
		}
	}

}

void EnemyCloakMan::Update(float dt)
{
	Enemy::Update(dt);
}
