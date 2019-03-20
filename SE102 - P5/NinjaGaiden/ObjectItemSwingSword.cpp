#include "ObjectItemSwingSword.h"

ObjectItemSwingSword::ObjectItemSwingSword()
{
	_animation = new Animation(ITEM, 3, 6);
	_isOnScreen = false;
	_width = ITEM_SWINGSWORD_WIDTH;
	_height = ITEM_SWINGSWORD_HEIGHT;
}

void ObjectItemSwingSword::Update(float dt)
{
}

void ObjectItemSwingSword::Render(float x, float y, int frameIndex)
{
	_animation->GetSprite(frameIndex)->FlipHorizontal(_isReverse);

	switch (frameIndex)
	{
	case 0:
		_animation->GetSprite(frameIndex)->Render(x + (_isReverse ? -10 : 10), y - 15);
		break;

	case 1:
		_animation->GetSprite(frameIndex)->Render(x + (_isReverse ? -3 : 3), y + 3);
		break;

	case 2:
		_animation->GetSprite(frameIndex)->Render(x - (_isReverse ? -10 : 10), y - 15);
		break;

	case 3:
		_animation->GetSprite(frameIndex)->Render(x, y - 18);
		break;
	}
}
