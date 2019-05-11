#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 11);
	tag = ENEMY;
	type = BULLET;
	this->height = ITEM_BULLET_HEIGHT;
	this->width = ITEM_BULLET_WIDTH;
	this->isOnScreen = false;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update(float dt, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		posX += vx * dt;
		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void EnemyBullet::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

