#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[FLYING] = new Animation(ENEMY, 18, 19, 150);
	curAnimation = animations[FLYING];
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
}

EnemyEagle::~EnemyEagle()
{
}
