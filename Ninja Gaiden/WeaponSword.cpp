#include "WeaponSword.h"

WeaponSword::WeaponSword()
{
	animation = new Animation(WEAPON, 3, 4, DEFAULT_TPS >> 1);
	isOnScreen = false;
	width = WEAPON_SWORD_WIDTH;
	height = WEAPON_SWORD_HEIGHT;
	vx = vy = 0;
	type = SWORD;
}

void WeaponSword::Update(float dt)
{

}

void WeaponSword::Render(float x, float y, int frameIndex, float translateX, float translateY)
{
	if (!isOnScreen || frameIndex == 0)
		return;

	Sprite* sprite = animation->GetSprite(--frameIndex);
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