#include "ObjectItemSwingSword.h"

ObjectItemSwingSword::ObjectItemSwingSword()
{
	_animation = new Animation(ITEM, 3, 6);
	isOnScreen = false;
	width = ITEM_SWINGSWORD_WIDTH;
	height = ITEM_SWINGSWORD_HEIGHT;
	tag = ITEM;
	type = SWINGSWORD;
}

void ObjectItemSwingSword::Update(float dt)
{
}

void ObjectItemSwingSword::Render(float x, float y, int frameIndex, float translateX, float translateY)
{
	if (!isOnScreen) return;

	Sprite* sprite = _animation->GetSprite(frameIndex);
	sprite->isReverse = this->isReverse;

	switch (frameIndex)
	{
	case 0:
		sprite->Render(x, y, translateX + (isReverse ? -10 : 10), translateY - 6);
		break;

	case 1:
		sprite->Render(x, y, translateX + (isReverse ? -3 : 3), translateY + 10);
		break;

	case 2:
		sprite->Render(x, y, translateX + (isReverse ? 10 : -10), translateY - 4);
		break;

	case 3:
		sprite->Render(x, y, translateX + (isReverse ? 2 : -2), translateY - 10);
		break;
	}
}