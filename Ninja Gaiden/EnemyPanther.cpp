#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[STANDING] = new Animation(ENEMY, 15, 15);
	animations[RUNNING] = new Animation(ENEMY, 15, 16);
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
	speed = ENEMY_PANTHER_SPEED;
	score = ENEMY_PANTHER_SCORE;
}

EnemyPanther::~EnemyPanther()
{
}

void EnemyPanther::DetectGround(std::unordered_set<Rect*> grounds)
{
	Enemy::DetectGround(grounds);
	curGroundBound = groundBound;
	isOnGround = true;
}

void EnemyPanther::DetectCurGround(std::unordered_set<Rect*> grounds)
{
	Rect nextGround = curGroundBound;

	for (auto g : grounds)
	{
		if (g->y < this->posY - (this->height >> 1))
		{
			if (this->isReverse)
			{
				if (g->x <= curGroundBound.x && (nextGround.x == curGroundBound.x || g->x > nextGround.x))
				{
					nextGround = (*g);
				}
			}
			else
			{
				if (g->x >= curGroundBound.x && (nextGround.x == curGroundBound.x || g->x < nextGround.x))
				{
					nextGround = (*g);
				}
			}
		}
	}
	curGroundBound = nextGround;
}

void EnemyPanther::UpdateDistance(float dt)
{
	if (this->posY - (this->height >> 1) <= this->curGroundBound.y)
	{
		this->vy = 0;
		this->posY = this->curGroundBound.y + (this->height >> 1);
	}

	this->isOnGround = (this->posX > curGroundBound.x
		&& this->posX < curGroundBound.x + curGroundBound.width);

	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyPanther::ChangeState(State StateName)
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
			this->curGroundBound = groundBound;
			this->isOnGround = true;
			this->isActive = true;
		}
		break;
	}

	case DEAD:
	{
		scoreboard->score += score;
		Sound::getInstance()->play("enemydie");
		break;
	}
	}
	this->StateName = StateName;
	this->curAnimation = animations[StateName];
}