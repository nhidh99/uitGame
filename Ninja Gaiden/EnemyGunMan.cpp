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
	vx = ENEMY_GUNMAN_VX;
}

EnemyGunMan::~EnemyGunMan()
{
}

void EnemyGunMan::Update(float dt)
{
 	Enemy::Update(dt);


	if (abs(this->posX - player->posX) <= 100)
	{
		this->curAnimation = animations[ATTACKING];
		this->vx = 0;
	}
	else
	{
		this->curAnimation = animations[RUNNING];
		//this->vx = 0.01f;
	}

	//if (bullet->isOnScreen == false)
	//{
	//	bullet->isOnScreen = true;
	//	bullet->posX = this->posX - 12;
	//	bullet->posY = this->posY + 7;
	//}

	//if (bullet->isOnScreen) 
	//{
	//	bullet->Update(dt, camera->GetRect());
	//}
}

void EnemyGunMan::Render(float translateX, float translateY)
{	
	Enemy::Render(translateX, translateY);	
	bullet->Render(0, 0);
}
