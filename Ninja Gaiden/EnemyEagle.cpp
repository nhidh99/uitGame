#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[STANDING] = new Animation(ENEMY, 18, 18, 150);
	animations[ATTACKING] = new Animation(ENEMY, 18, 19, 150);
	curAnimation = animations[ATTACKING];
	tag = ENEMY;
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	vx = ENEMY_EAGLE_VX;
	vy = ENEMY_EAGLE_VY;
}

EnemyEagle::~EnemyEagle()
{
}

void EnemyEagle::Update(float dt)
{
	Enemy::Update(dt);
}

