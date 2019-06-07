#include "EnemyBoss.h"

EnemyBoss::EnemyBoss()
{
	animations[STANDING] = new Animation(ENEMY, 21);
	animations[RUNNING] = new Animation(ENEMY, 21);
	animations[JUMPING] = new Animation(ENEMY, 22);
	animations[DEAD] = new Animation(WEAPON, 13);
	tag = ENEMY;
	type = BOSS;
	width = ENEMY_BOSS_WIDTH;
	height = ENEMY_BOSS_HEIGHT;
	speed = delayTime = 0;
	bulletCountdown = 3;
	firstJump = true;
	delayDead = 3000;
}

void EnemyBoss::UpdateDistance(float dt)
{
	if (StateName == DEAD) return;

	if (delayTime <= 0)
	{
		--bulletCountdown;
		this->ChangeState(JUMPING);
		delayTime = 1200;
	}
	else
	{
		delayTime -= dt;
		if (StateName == JUMPING)
		{
			this->vy -= 0.012f;
		}

		if (this->posX - (this->width >> 1) + dx <= 30)
		{
			this->dx = 0;
			this->posX = 30 + (this->width >> 1);
		}
		else if (this->posX + (this->width >> 1) + dx >= 230)
		{
			this->dx = 0;
			this->posX = 230 - (this->width >> 1);
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

	if (this->StateName == DEAD)
	{
		delayDead -= dt;

		if (isFrozenEnemies)
		{
			curAnimation->Update(dt);
		}

		if (delayDead <= 0)
		{
			this->isDead = true;
			this->isActive = false;
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
		this->vy = 0.35f;
		if (!firstJump)
		{
			this->isReverse = !this->isReverse;
			this->vx = isReverse ? -0.175f : 0.175f;
		}
		else this->vx = -0.175f;
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		break;
	}
	}

	this->StateName = StateName;

	if (StateName != DEAD)
	{
		this->curAnimation = animations[StateName];
	}
}

void EnemyBoss::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;
	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY);

	if (StateName == DEAD)
	{
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
