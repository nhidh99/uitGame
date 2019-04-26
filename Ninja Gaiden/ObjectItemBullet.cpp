#include "ObjectItemBullet.h"

ObjectItemBullet::ObjectItemBullet()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 11);
	tag = ITEM;
	type = BULLET;
	this->height = ITEM_BULLET_HEIGHT;
	this->width = ITEM_BULLET_WIDTH;
	this->isOnScreen = false;
}

ObjectItemBullet::~ObjectItemBullet()
{
}

void ObjectItemBullet::Update(float dt, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		posX += vx * dt;
		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void ObjectItemBullet::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

