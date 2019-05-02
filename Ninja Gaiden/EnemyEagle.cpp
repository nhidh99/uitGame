#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[FLYING] = new Animation(ENEMY, 18, 19, 150);
	curAnimation = animations[FLYING];
	tag = ENEMY;
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	vx = 0.02;
}

EnemyEagle::~EnemyEagle()
{
}
