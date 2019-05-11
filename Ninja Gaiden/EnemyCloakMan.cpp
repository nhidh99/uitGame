#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[RUNNING] = new Animation(ENEMY, 12, 13, 150);
	animations[ATTACKING] = new Animation(ENEMY, 13, 14, 150);
	curAnimation = animations[ATTACKING];
	dagger = new EnemyDagger();
	tag = ENEMY;
	type = CLOAKMAN;
	height = ENEMY_CLOAKMAN_HEIGHT;	
	width = ENEMY_CLOAKMAN_WIDTH;
}

EnemyCloakMan::~EnemyCloakMan()
{
}

void EnemyCloakMan::Render(float translateX, float translateY)
{
	Enemy::Render(translateX, translateY);

	if (dagger->isOnScreen)
	{
		dagger->Render(translateX, translateY);
	}
}

void EnemyCloakMan::Update(float dt, Rect camRect)
{
	Enemy::Update(dt, camRect);

	if (curAnimation->isLastFrame != true && dagger->isOnScreen == false)
	{
		dagger->isOnScreen = true;
		dagger->posX = this->posX - 5;
		dagger->posY = this->posY - 10;
		dagger->maxHigh = dagger->posY - 20;
	}

 	if (dagger->isOnScreen)
	{
		dagger->Update(dt, camRect);
	}
	if (dagger->isOutCam(camRect))
	{
		dagger->posX = this->posX - 5;
		dagger->posY = this->posY - 10;
		dagger->vy = -0.06;
	}
}
