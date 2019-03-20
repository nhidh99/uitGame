#include "ObjectItemSword.h"

ObjectItemSword::ObjectItemSword()
{
	_animation = new Animation(ITEM, 0, 1, TIME_PER_FRAME >> 1);
	_isOnScreen = false;
	_width = ITEM_SWORD_WIDTH;
	_height = ITEM_SWORD_HEIGHT;
}

void ObjectItemSword::Update(float dt)
{
}

void ObjectItemSword::Render(float x, float y, int frameIndex)
{
	if (frameIndex == 0)
		return;

	_animation->GetSprite(--frameIndex)->FlipHorizontal(_isReverse);

	switch (frameIndex)
	{
	case 0:
		_animation->GetSprite(frameIndex)->Render(x + (_isReverse ? -20 : 20), y - 24);
		break;

	case 1:
		_animation->GetSprite(frameIndex)->Render(x + (_isReverse ? -12 : 12), y - 18);
		_isOnScreen = false;
		break;
	}
}