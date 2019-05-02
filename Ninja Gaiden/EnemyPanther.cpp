#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[RUNNING] = new Animation(ENEMY, 16, 17, 150);
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
}

EnemyPanther::~EnemyPanther()
{
}
