#include "EnemyGunMan.h"

EnemyGunMan::EnemyGunMan()
{
	animations[STANDING] = new Animation(ENEMY, 7, 7);
	animations[RUNNING] = new Animation(ENEMY, 7, 8);
	animations[ATTACKING] = new Animation(ENEMY, 9, 10, DEFAULT_TPF >> 2);
	type = GUNMAN;
	height = ENEMY_GUNMAN_HEIGHT;
	width = ENEMY_GUNMAN_WIDTH;
	speed = ENEMY_GUNMAN_SPEED;
	delayTime = ENEMY_GUNMAN_DELAY_TIME >> 1;
	bullets = bulletCount = BULLET_GUNMAN_COUNT;
	score = ENEMY_GUNMAN_SCORE;
}

EnemyGunMan::~EnemyGunMan()
{
}

void EnemyGunMan::UpdateDistance(float dt)
{
	this->isReverse = (player->posX < this->posX);
	delayTime -= dt;

	switch (this->StateName)
	{
	case RUNNING:
	{
		this->dx = vx * dt;

		if ((vx > 0 && this->posX + (this->width >> 1) >= groundBound.x + groundBound.width)
			|| (vx < 0 && this->posX - (this->width >> 1) <= groundBound.x))
		{
			this->vx = -vx;
		}

		if (delayTime <= 0)
		{
			this->ChangeState(ATTACKING);
			this->vx = -vx;
			delayTime = ENEMY_GUNMAN_DELAY_TIME;
		}
		break;
	}
	case ATTACKING:
	{
		this->dx = 0;
		break;
	}
	}
}

void EnemyGunMan::Update(float dt)
{
	Enemy::Update(dt);
	if (this->isDead)
	{
		delayTime = ENEMY_CLOAKMAN_DELAY_TIME >> 1;
	}
}
