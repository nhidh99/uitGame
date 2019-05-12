#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[STANDING] = new Animation(ENEMY, 18, 18, 150);
	animations[ATTACKING] = new Animation(ENEMY, 18, 19, 150);
	tag = ENEMY;
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	vx = 0.02;
}

EnemyEagle::~EnemyEagle()
{
}
