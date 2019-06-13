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

void EnemyRunMan::DetectCurGround(std::unordered_set<Rect*> grounds)
{
	for (auto g : grounds)
	{
		if (this->posX >= g->x && this->posX <= g->x + g->width &&
			this->posY - (this->height >> 1) <= g->y && this->posY > g->y)
		{
			this->vy = 0;
			this->posY = g->y + (this->height >> 1);
			this->curGroundBound = *g;
			this->isOnGround = true;
			this->curAnimation = animations[RUNNING];
			break;
		}
	}
}

void EnemyRunMan::UpdateDistance(float dt)
{
	if (!this->isOnGround) this->vy -= GRAVITY_SPEED;

	if (this->isOnGround && ((this->vx < 0 && this->posX - 30 < curGroundBound.x)
		|| (this->vx > 0 && this->posX + 30 > curGroundBound.x + curGroundBound.width)))
	{
		this->isOnGround = false;
		this->vy = ENEMY_RUNMAN_JUMP_SPEED;
		this->curAnimation = animations[STANDING];
	}

	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyRunMan::ChangeState(State StateName)
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
			this->vy = 0;
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
