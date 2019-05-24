#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[STANDING] = new Animation(ENEMY, 15, 15);
	animations[ATTACKING] = new Animation(ENEMY, 15, 16);
	tag = ENEMY;
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
}

EnemyPanther::~EnemyPanther()
{
}
