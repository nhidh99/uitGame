#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[RUNNING] = new Animation(ENEMY, 12, 13, 150);
	animations[ATTACKING] = new Animation(ENEMY, 14, 14, 150);
	curAnimation = animations[RUNNING];
	type = CLOAKMAN;
	height = ENEMY_CLOAKMAN_HEIGHT;	
	width = ENEMY_CLOAKMAN_WIDTH;
	vx = -0.02;
}

EnemyCloakMan::~EnemyCloakMan()
{
}
