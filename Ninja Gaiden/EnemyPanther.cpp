#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[STANDING] = new Animation(ENEMY, 16, 16);
	animations[ATTACKING] = new Animation(ENEMY, 16, 17);
	curAnimation = animations[ATTACKING];
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
	if (this->posY < 46)
	{
		if (this->vy < 0)
		{
			this->vy = -this->vy;
		}
	}

}
