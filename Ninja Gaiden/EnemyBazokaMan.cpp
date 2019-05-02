#include "EnemyBazokaMan.h"

EnemyBazokaMan::EnemyBazokaMan()
{
	animations[SITTING] = new Animation(ENEMY, 0, 2, 150);
	curAnimation = animations[SITTING];
	type = BAZOKAMAN;
	tag = ENEMY;
	height = ENEMY_BAZOKAMAN_HEIGHT;
	width = ENEMY_BAZOKAMAN_WIDTH;
	vy = 0;
}