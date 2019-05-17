#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[RUNNING] = new Animation(ENEMY, 0, 2, 125);
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
	vx = ENEMY_SWORDMAN_VX;
}

EnemySwordMan::~EnemySwordMan()
{
}

void EnemySwordMan::Update(float dt)
{
	Enemy::Update(dt);

	//if (abs(this->posX - player->posX) <= 100)
	//{
	//	this->curAnimation = animations[ATTACKING];
	//	this->vx = 0;
	//}
	//else
	//{
	//	this->curAnimation = animations[RUNNING];
	//	//this->vx = 0.01f;
	//}
}
