#include "EnemyCloakMan.h"

EnemyCloakMan::EnemyCloakMan()
{
	animations[RUNNING] = new Animation(ENEMY, 12, 13, 150);
	animations[ATTACKING] = new Animation(ENEMY, 13, 14, 150);
	curAnimation = animations[ATTACKING];
	dagger = new ObjectItemDagger();
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

	if (curAnimation->isLastFrame == true && dagger->isOnScreen == false)
	{
		dagger->isOnScreen = true;
		dagger->posX = this->posX - 5;
		dagger->posY = this->posY - 10;
	}

	if (dagger->isOnScreen)
	{
		dagger->Update(dt, this->posY - 50, 0, 1500);
	}
}
