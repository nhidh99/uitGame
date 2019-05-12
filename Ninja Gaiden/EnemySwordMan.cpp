#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[STANDING] = new Animation(ENEMY, 0, 0);
	animations[ATTACKING] = new Animation(ENEMY, 0, 2);
	tag = ENEMY;
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
}

EnemySwordMan::~EnemySwordMan()
{
}