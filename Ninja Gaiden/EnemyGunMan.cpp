#include "EnemyGunMan.h"

EnemyGunMan::EnemyGunMan()
{
	animations[STANDING] = new Animation(ENEMY, 7, 7);
	animations[RUNNING] = new Animation(ENEMY, 7, 8);
	animations[ATTACKING] = new Animation(ENEMY, 9, 10);
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = GUNMAN;
	height = ENEMY_GUNMAN_HEIGHT;
	width = ENEMY_GUNMAN_WIDTH;
	vx = ENEMY_GUNMAN_VX;
}

EnemyGunMan::~EnemyGunMan()
{
}

void EnemyGunMan::Update(float dt)
{
	Enemy::Update(dt);
}

void EnemyGunMan::Render(float translateX, float translateY)
{
	Enemy::Render(translateX, translateY);

}
