#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[STANDING] = new Animation(ENEMY, 16, 16);
	animations[ATTACKING] = new Animation(ENEMY, 16, 17);
	tag = ENEMY;
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
}

EnemyPanther::~EnemyPanther()
{
}
