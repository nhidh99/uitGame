#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[RUNNING] = new Animation(ENEMY, 12, 13, 150);
	animations[ATTACKING] = new Animation(ENEMY, 13, 14, 150);
	curAnimation = animations[RUNNING];
	this->vx = ENEMY_CLOAKMAN_VX;
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

void EnemyCloakMan::Update(float dt)
{
	Enemy::Update(dt);

	if (abs(this->posX - player->posX) <= 50 )
	{
		this->curAnimation = animations[ATTACKING];
		this->vx = 0;
	}
	else
	{
		this->curAnimation = animations[RUNNING];
		//this->vx = 0.01f;
	}


	/*if (curAnimation->isLastFrame != true && dagger->isOnScreen == false)
	{
		dagger->isOnScreen = true;
		dagger->posX = this->posX - 5;
		dagger->posY = this->posY - 10;
		dagger->maxHigh = dagger->posY - 20;
	}

 	if (dagger->isOnScreen)
	{
		dagger->Update(dt);
	}*/
}
