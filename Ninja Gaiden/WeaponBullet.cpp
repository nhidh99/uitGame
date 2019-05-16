#include "WeaponBullet.h"

WeaponBullet::WeaponBullet()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 11);
	type = BULLET;
	this->height = WEAPON_BULLET_HEIGHT;
	this->width = WEAPON_BULLET_WIDTH;
	this->isOnScreen = false;
}

WeaponBullet::~WeaponBullet()
{
}

void WeaponBullet::Update(float dt, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		posX += vx * dt;
		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void WeaponBullet::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

