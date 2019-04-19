#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[RUNNING] = new Animation(ENEMY, 0, 2, 125);
	//--
	curAnimation = animations[RUNNING];
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
	vy = 0;
}

EnemySwordMan::~EnemySwordMan()
{
}