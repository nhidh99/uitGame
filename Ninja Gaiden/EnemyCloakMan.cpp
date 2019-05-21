#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[STANDING] = new Animation(ENEMY, 12, 12);
	animations[ATTACKING] = new Animation(ENEMY, 12, 14);
	curAnimation = animations[ATTACKING];
	tag = ENEMY;
	type = CLOAKMAN;
	height = ENEMY_CLOAKMAN_HEIGHT;	
	width = ENEMY_CLOAKMAN_WIDTH;
	vx = ENEMY_CLOAKMAN_VX;
}

EnemyCloakMan::~EnemyCloakMan()
{
}

void EnemyCloakMan::Render(float translateX, float translateY)
{
	Enemy::Render(translateX, translateY);
}

void EnemyCloakMan::Update(float dt)
{
	Enemy::Update(dt);
}
