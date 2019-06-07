﻿#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[STANDING] = new Animation(ENEMY, 17, 17, DEFAULT_TPS >> 1);
	animations[RUNNING] = new Animation(ENEMY, 17, 18, DEFAULT_TPS >> 1);
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	delayTime = ENEMY_EAGLE_DELAY_TIME >> 1;
}

void EnemyEagle::UpdateDistance(float dt)
{
	this->isReverse = (player->posX < this->posX);

	if (delayTime <= 0)
	{
		this->dx = (player->posX - this->posX) / MAX_FRAME_RATE;
		this->dy = (player->posY - this->posY) / MAX_FRAME_RATE;

		if (player->posX < this->posX)
		{
			this->dx = min(-ENEMY_EAGLE_MIN_SPEEDX, dx);
		}
		else
		{
			this->dx = max(ENEMY_EAGLE_MIN_SPEEDX, dx);
		}

		if (player->posY < this->posY)
		{
			this->dy = min(-ENEMY_EAGLE_MIN_SPEEDY, dy);
		}
		else this->dy = max(ENEMY_EAGLE_MIN_SPEEDY, dy);

		delayTime = ENEMY_EAGLE_DELAY_TIME;
	}
	else
	{
		delayTime -= dt;
	}

	// Đạp phanh khi bay hố =))

	if (dx > 0 && this->posX > player->posX)
	{
		this->dx -= 0.05f;
	}
	else if (dx < 0 && this->posX <= player->posX)
	{
		this->dx += 0.05f;
	}

	if (dy > 0 && this->posY > player->posY)
	{
		this->dy -= 0.035f;
	}
	else if (dy < 0 && this->posY <= player->posY)
	{
		this->dy += 0.035f;
	}
}

void EnemyEagle::Update(float dt)
{
	Enemy::Update(dt);

	if (this->isDead)
	{
		delayTime = ENEMY_EAGLE_DELAY_TIME >> 1;
	}
}

void EnemyEagle::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		this->isActive = false;
		this->isDead = false;
		this->isOutScreen = false;
		break;
	}

	case RUNNING:
	{
		auto distance = player->posX - this->spawnX;

		if (activeDistance * distance > 0 && distance >= this->activeDistance)
		{
			this->dx = this->dy = 0;
			this->isActive = true;
		}
		break;
	}
	}

	this->StateName = StateName;
	this->curAnimation = animations[StateName];
}
