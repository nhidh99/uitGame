#include "EnemyGunMan.h"

EnemyGunMan::EnemyGunMan()
{
	animations[RUNNING] = new Animation(ENEMY, 7, 8, 150);
	animations[ATTACKING] = new Animation(ENEMY, 9, 10, 150);
	curAnimation = animations[RUNNING];
	type = GUNMAN;
	height = ENEMY_GUNMAN_HEIGHT;
	width = ENEMY_GUNMAN_WIDTH;
}

EnemyGunMan::~EnemyGunMan()
{
}
