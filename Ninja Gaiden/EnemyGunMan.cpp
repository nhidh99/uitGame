#include "EnemyGunMan.h"

EnemyGunMan::EnemyGunMan()
{
	animations[RUNNING] = new Animation(ENEMY, 7, 8, 150);
	animations[ATTACKING] = new Animation(ENEMY, 9, 10, 150);
	bullet = new EnemyBullet();
	bullet->vx = -0.02;
	curAnimation = animations[RUNNING];
	tag = ENEMY;
	type = GUNMAN;
	height = ENEMY_GUNMAN_HEIGHT;
	width = ENEMY_GUNMAN_WIDTH;
	vx = 0.02;

	for (int i = 0; i < 3; i++)
	{
		EnemyBullet* bul = new EnemyBullet();
		bul->vx = -0.02;
		bul->isOnScreen = false;
		bullets.push_back(bul);
	}
}

EnemyGunMan::~EnemyGunMan()
{
}

void EnemyGunMan::Update(float dt, Rect camRect)
{
	Enemy::Update(dt, camRect);

	//Cho phép đạn xuất hiện khi xong animation bắn
	for (int i = 0; i < bullets.size(); i++) {
		if (curAnimation->isLastFrame == true && bullets[i]->isOnScreen == false)
		{
			bullets[i]->isOnScreen = true;
			bullets[i]->posX = this->posX - (7 * i);
			bullets[i]->posY = this->posY;
		}

		if (bullets[i]->isOnScreen)
		{
			bullets[i]->Update(dt, camRect);
		}
	}

}

void EnemyGunMan::Render(float translateX, float translateY)
{
	Enemy::Render(translateX, translateY);
	for (auto bul : bullets) {
		if (bul->isOnScreen == true)
		{
			bul->Render(translateX, translateY);
		}
	}
}
