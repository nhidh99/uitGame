#include "EnemyBoss.h"

EnemyBoss::EnemyBoss()
{
	animations[STANDING] = new Animation(ENEMY, 21);
	animations[RUNNING] = new Animation(ENEMY, 21);
	animations[JUMPING] = new Animation(ENEMY, 22);
	animations[DEAD] = new Animation(WEAPON, 13);
	tag = ENEMY;
	type = BOSS;
	health = ENEMY_BOSS_HEALTH;
	width = ENEMY_BOSS_WIDTH;
	height = ENEMY_BOSS_HEIGHT;
	bulletCountdown = BULLET_BOSS_COUNT;
	delayDead = ENEMY_BOSS_DELAY_DEATH;
	delayHit = ENEMY_BOSS_DELAY_HIT;
	speed = delayJump = 0;
	firstJump = true;
}

void EnemyBoss::UpdateDistance(float dt)
{
	if (StateName == DEAD) return;

	if (delayJump <= 0)
	{
		--bulletCountdown;
		this->ChangeState(JUMPING);
		delayJump = ENEMY_BOSS_DELAY_JUMP;
	}
	else
	{
		delayJump -= dt;
		if (StateName == JUMPING)
		{
			this->vy -= GRAVITY_SPEED;
		}

		if (this->posX - (this->width >> 1) + dx <= ENEMY_BOSS_LEFT)
		{
			this->dx = 0;
			this->posX = ENEMY_BOSS_LEFT + (this->width >> 1);
		}
		else if (this->posX + (this->width >> 1) + dx >= ENEMY_BOSS_RIGHT)
		{
			this->dx = 0;
			this->posX = ENEMY_BOSS_RIGHT - (this->width >> 1);
		}

		if (this->posY - (this->height >> 1) + dy < this->groundBound.y)
		{
			this->ChangeState(STANDING);
			this->posY = this->groundBound.y + (this->height >> 1);
		}
	}

	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyBoss::Update(float dt)
{
	if (isFrozenEnemies)
	{
		this->dx = this->dy = 0;
	}
	else
	{
		this->UpdateDistance(dt);
		curAnimation->Update(dt);
	}

	if (delayHit)
	{
		delayHit -= dt;
		if (delayHit <= 0)
		{
			delayHit = 0;
		}
	}

	if (this->StateName == DEAD)
	{
		delayDead -= dt;

		if (isFrozenEnemies)
		{
			curAnimation->Update(dt);
		}

		if (delayDead <= 0)
		{
			Sound::getInstance()->stop("bossdie");
			this->isDead = true;
			this->isActive = false;
			isEndGame = true;
		}
	}
}

void EnemyBoss::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		firstJump = false;
		break;
	}

	case RUNNING:
	{
		this->isActive = true;
		break;
	}

	case JUMPING:
	{
		this->vy = ENEMY_BOSS_JUMP_SPEED;
		if (!firstJump)
		{
			this->isReverse = !this->isReverse;
			this->vx = isReverse ? -ENEMY_BOSS_SPEED : ENEMY_BOSS_SPEED;
		}
		else this->vx = -ENEMY_BOSS_SPEED;
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		Sound::getInstance()->play("bossdie", true);
		break;
	}
	}

	this->StateName = StateName;

	if (StateName != DEAD)
	{
		this->curAnimation = animations[StateName];
	}
}

void EnemyBoss::SubtractHealth()
{
	if (!delayHit)
	{
		--this->health;
		--scoreboard->bossHealth;
		this->delayHit = ENEMY_BOSS_DELAY_HIT;

		if (this->health == 0)
		{
			this->ChangeState(DEAD);
		}
	}
}

void EnemyBoss::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;
	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY + SCREEN_TRANSLATEY);

	if (StateName == DEAD)
	{
		posY += SCREEN_TRANSLATEY;
		switch (explodeTimes)
		{
		case 0:
			animations[DEAD]->Render(posX + 5, posY);
			animations[DEAD]->Render(posX - 10, posY + 15);
			animations[DEAD]->Render(posX - 10, posY - 15);
			break;

		case 2:
			animations[DEAD]->Render(posX - 5, posY);
			animations[DEAD]->Render(posX + 10, posY + 15);
			animations[DEAD]->Render(posX + 10, posY - 15);
			break;

		case 3:
			explodeTimes = -1;
			break;
		}
		++explodeTimes;
	}
}
