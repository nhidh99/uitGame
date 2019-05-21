#include "EnemySwordMan.h"

EnemySwordMan::EnemySwordMan()
{
	animations[STANDING] = new Animation(ENEMY, 0, 0);
	animations[ATTACKING] = new Animation(ENEMY, 0, 2);
	curAnimation = animations[ATTACKING];
	tag = ENEMY;
	type = SWORDMAN;
	width = ENEMY_SWORDMAN_WIDTH;
	height = ENEMY_SWORDMAN_HEIGHT;
	vx = ENEMY_SWORDMAN_VX;
}

EnemySwordMan::~EnemySwordMan()
{
}

void EnemySwordMan::Update(float dt)
{
	Enemy::Update(dt);
}
