#include "EnemyGunMan.h"

EnemyGunMan::EnemyGunMan()
{
	animations[RUNNING] = new Animation(ENEMY, 7, 8, 150);
	animations[ATTACKING] = new Animation(ENEMY, 9, 10, 150);
	bullet = new ObjectItemBullet();
	bullet->vx = -0.02;
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = GUNMAN;
	height = ENEMY_GUNMAN_HEIGHT;
	width = ENEMY_GUNMAN_WIDTH;
	vx = 0.02;
}

EnemyGunMan::~EnemyGunMan()
{
}

void EnemyGunMan::Update(float dt)
{
	Enemy::Update(dt);

	//Cho phép đạn xuất hiện khi xong animation bắn
	if (curAnimation->isLastFrame == true && bullet->isOnScreen == false)
	{
		bullet->isOnScreen = true;
		bullet->posX = this->posX - 7;
		bullet->posY = this->posY;
	}

	if (bullet->isOnScreen)
	{
		bullet->Update(dt, 500, 1500);
	}
}

void EnemyGunMan::Render(float translateX, float translateY)
{
	Enemy::Render(translateX, translateY);

	if (bullet->isOnScreen == true)
	{
		bullet->Render(translateX, translateY);
	}
}
