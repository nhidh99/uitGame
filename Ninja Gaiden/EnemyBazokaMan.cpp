#include "EnemyBazokaMan.h"

EnemyBazokaMan::EnemyBazokaMan()
{
	animations[STANDING] = new Animation(ENEMY, 0, 0);
	animations[ATTACKING] = new Animation(ENEMY, 0, 2);
	type = BAZOKAMAN;
	tag = ENEMY;
	height = ENEMY_BAZOKAMAN_HEIGHT;
	width = ENEMY_BAZOKAMAN_WIDTH;
	vy = 0;
}