#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[RUNNING] = new Animation(ENEMY, 0, 2, 150);
	curAnimation = animations[RUNNING];
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
	vy = 0;
	//vx = -0.01;
}

EnemySwordMan::~EnemySwordMan()
{
}