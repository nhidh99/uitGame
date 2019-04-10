#include "EnemyPanther.h"

EnemyPanther::EnemyPanther()
{
	animations[RUNNING] = new Animation(ENEMY, 16, 17, 150);
	curAnimation = animations[RUNNING];
	type = PANTHER;
	height = ENEMY_PANTHER_HEIGHT;
	width = ENEMY_PANTHER_WIDTH;
	//vx = -0.01;
}

EnemyPanther::~EnemyPanther()
{
}
