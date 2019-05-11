#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[FLYING] = new Animation(ENEMY, 18, 19, 50);
	curAnimation = animations[FLYING];
	tag = ENEMY;
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	vx = -0.05;
	vy = 0.02;
	reversePointX = 439;
	reversePointY = 91;
	maxDepth = 113;
	maxHigh = 19;
}

EnemyEagle::~EnemyEagle()
{
}

void EnemyEagle::Update(float dt, Rect camRect)
{
	Enemy::Update(dt, camRect);

	if (this->posX <= reversePointX && this->posY > reversePointY)
	{
		this->isReverse = false;
	}
	if (this->posY >= maxDepth || this->posY <= maxHigh)
	{
		this->vy = -this->vy;
		this->vx = -this->vx;
	}
}
