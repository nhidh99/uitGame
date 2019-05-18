#include "WeaponSwingSword.h"

WeaponSwingSword::WeaponSwingSword()
{
	_animation = new Animation(WEAPON, 5, 8);
	isOnScreen = false;
	width = WEAPON_SWINGSWORD_WIDTH;
	height = WEAPON_SWINGSWORD_HEIGHT;
	type = SWINGSWORD;
}

void WeaponSwingSword::Update(float dt)
{
}

void WeaponSwingSword::Render(float x, float y, int frameIndex, float translateX, float translateY)
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