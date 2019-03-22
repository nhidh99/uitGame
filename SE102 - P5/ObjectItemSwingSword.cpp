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

void ObjectItemSwingSword::Render(float x, float y, int frameIndex)
{
	if (!isOnScreen) return;

	Sprite* sprite = _animation->GetSprite(frameIndex);
	sprite->isReverse = this->isReverse;

	switch (frameIndex)
	{
	case 0:
		sprite->Render(x, y, isReverse ? -10 : 10, -6);
		break;

	case 1:
		sprite->Render(x, y, isReverse ? -3 : 3, 10);
		break;

	case 2:
		sprite->Render(x, y, isReverse ? 10 : -10, -4);
		break;

	case 3:
		sprite->Render(x, y, isReverse ? 2 : -2, -10);
		break;
	}
}