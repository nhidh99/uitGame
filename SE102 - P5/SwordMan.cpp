#include "SwordMan.h"

RECT SwordMan::GetBound()
{
	RECT bound;
	bound.left = posX;
	bound.right = posX + width;
	bound.top = posY;
	bound.bottom = posY + height;
	return bound;
}

SwordMan::SwordMan()
{
	animation = new Animation(ENEMY, 0, 2, 125);
	deadSprite = new EnemySprite(SWORDMAN, 0, 0, 30, 38);
	tag = ENEMY;
	type = SWORDMAN;
	width = 30;
	height = 48;
	vx = 0;
}

SwordMan::~SwordMan()
{
}

void SwordMan::Render()
{
	animation->isReverse = this->isReverse;
	animation->Render(posX, posY);
}

void SwordMan::Render(float translateX, float translateY)
{
	animation->isReverse = this->isReverse;
	animation->Render(posX, posY, translateX, translateY);
}

void SwordMan::Update(float dt)
{
	animation->Update(dt);
	posX += vx * dt;
}

bool SwordMan::IsLastFrame()
{
	if (animation->isLastFrame)
		return true;
	return false;
}

