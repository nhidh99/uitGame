#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[FLYING] = new Animation(ENEMY, 18, 19, 100);
	curAnimation = animations[FLYING];
	tag = ENEMY;
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	vx = ENEMY_EAGLE_VX;
	vy = ENEMY_EAGLE_VY;
	reversePointX = player->posX;
	reversePointY = 91;
	maxDepth = player->posY;
	maxHigh = 19;
}

EnemyEagle::~EnemyEagle()
{
}

void EnemyEagle::Update(float dt)
{
	Enemy::Update(dt);


	if (this->posY < player->posY)
	{
		this->vy = -vy;
	}

	this->dx = vx * dt;
	this->dy = 30 * sin(dx * 3.14 / 180);
	/*if (this->posY < player->posY)
	{
		this->vy += 0.1f;
		this->vx = -this->vx;
	}*/
	/*if (this->posX <= reversePointX && this->posY > reversePointY)
	{
		this->isReverse = false;
	}
	if (this->posY >= maxDepth || this->posY <= maxHigh)
	{
		this->vy = -this->vy;
		this->vx = -this->vx;
	}*/
}
