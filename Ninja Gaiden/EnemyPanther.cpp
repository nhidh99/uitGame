#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[RUNNING] = new Animation(ENEMY, 16, 17, 150);
	animations[SCOLDED] = new Animation(ENEMY, 17, 17, 200);
	curAnimation = animations[RUNNING];
	this->vy = 0.05;
	tag = ENEMY;
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
	vx = ENEMY_PANTHER_VX;
	vy = ENEMY_PANTHER_VY;
}

EnemyPanther::~EnemyPanther()
{
}

void EnemyPanther::Update(float dt)
{
	Enemy::Update(dt);

	if (this->posY > 55)
	{
		if (this->vy > 0)
		{
			this->vy = -this->vy;
		}
	}
	
	if(this->posY < 46)
	{
		if (this->vy < 0)
		{
			this->vy = -this->vy;
		}
	}
}




