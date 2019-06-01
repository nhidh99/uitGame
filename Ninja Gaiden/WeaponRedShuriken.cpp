#include "WeaponRedShuriken.h"

WeaponRedShuriken::WeaponRedShuriken()
{
	animation = new Animation(WEAPON, 11, 12, DEFAULT_TPS >> 1);
	width = WEAPON_BLUESHURIKEN_WIDTH;
	height = WEAPON_BLUESHURIKEN_HEIGHT;
	vx = 0.6f;
	type = REDSHURIKEN;
}

void WeaponRedShuriken::UpdateDistance(float dt)
{
	dx = vx * dt;
	dy = 1.5 * (player->posY - this->posY) / MAX_FRAME_RATE;

	if (this->posX > player->posX)
	{
		if (vx > 0)
		{
			dx = min(3.5f, dx);
		}
		vx -= 0.014f;

		if (this->isReverse)
		{
			dy -= 0.4f;
		}
		else dy += 0.4f;
	}
	else
	{
		if (vx < 0)
		{
			dx = max(-3.5f, dx);
		}
		vx += 0.014f;

		if (this->isReverse)
		{
			dy += 0.4f;
		}
		else dy -= 0.4f;
	}

	if (this->GetRect().IsContain(player->GetRect()))
	{
		if (!isOut)
		{
			isOut = true;
			this->posX = player->posX + (isReverse ? -player->width : player->width);
		}
		else isDead = true;
	}
}
