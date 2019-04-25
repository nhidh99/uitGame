#include "ObjectItemSword.h"

ObjectItemSword::ObjectItemSword()
{
	_animation = new Animation(ITEM, 0, 1, DEFAULT_TPS >> 1);
	isOnScreen = false;
	width = ITEM_SWORD_WIDTH;
	height = ITEM_SWORD_HEIGHT;
	tag = ITEM;
	type = SWORD;
}

void ObjectItemSword::Update(float dt)
{
}

void ObjectItemSword::Render(float x, float y, int frameIndex, float translateX, float translateY)
{
	if (!isOnScreen || frameIndex == 0)
		return;

	Sprite* sprite = _animation->GetSprite(--frameIndex);
	sprite->isReverse = this->isReverse;

	switch (frameIndex)
	{
	case 0:
		sprite->Render(x, y, translateX + (isReverse ? -22 : 22), translateY - 10);
		break;

	case 1:
		sprite->Render(x, y, translateX + (isReverse ? -13 : 13), translateY - 10);
		isOnScreen = false;
		break;
	}
}