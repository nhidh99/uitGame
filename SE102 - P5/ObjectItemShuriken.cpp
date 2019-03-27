#include "ObjectItemShuriken.h"

ObjectItemShuriken::ObjectItemShuriken()
{
	_sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 2);
	isOnScreen = false;
	width = ITEM_SHURIKEN_WIDTH;
	height = ITEM_SHURIKEN_HEIGHT;
	tag = ITEM;
	type = SHURIKEN;
}

void ObjectItemShuriken::Update(float dt, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		posX += vx * dt;
		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void ObjectItemShuriken::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		_sprite->isReverse = this->isReverse;
		_sprite->Render(posX, posY, translateX, translateY);
	}
}