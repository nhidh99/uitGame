#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[RUNNING] = new Animation(ENEMY, 16, 17, 100);
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
	this->vx = -0.06;
	this->vy = -0.02;
}

EnemyPanther::~EnemyPanther()
{
}

void EnemyPanther::Update(float dt, Rect camRect)
{
	if (this->posY < 119)
	{
		this->vy = 0.02;
	}
	if (this->posY > 136)
	{
		this->vy = -0.02;
	}

	Enemy::Update(dt, camRect);
}
