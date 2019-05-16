#include "WeaponShuriken.h"

WeaponShuriken::WeaponShuriken()
{
	_sprite = SpriteFactory::GetInstance()->GetSprite(WEAPON, 4);
	isOnScreen = false;
	width = WEAPON_SHURIKEN_WIDTH;
	height = WEAPON_SHURIKEN_HEIGHT;
	type = SHURIKEN;
}

void WeaponShuriken::Update(float dt, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		posX += vx * dt;
		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void WeaponShuriken::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		_sprite->isReverse = this->isReverse;
		_sprite->Render(posX, posY, translateX, translateY);
	}
}