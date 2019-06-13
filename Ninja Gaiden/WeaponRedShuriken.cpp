#include "WeaponRedShuriken.h"

WeaponRedShuriken::WeaponRedShuriken()
{
	animation = new Animation(WEAPON, 11, 12, DEFAULT_TPF >> 1);
	width = WEAPON_REDSHURIKEN_WIDTH;
	height = WEAPON_REDSHURIKEN_HEIGHT;
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
			dx = min(WEAPON_REDSHURIKEN_MAX_DISTANCEX, dx);
		}
		vx -= WEAPON_REDSHURIKEN_REVERSE_ACCELERATEX;

		if (this->isReverse)
		{
			dy -= WEAPON_REDSHURIKEN_REVERSE_DISTANCEY;
		}
		else dy += WEAPON_REDSHURIKEN_REVERSE_DISTANCEY;
	}
	else
	{
		if (vx < 0)
		{
			dx = max(-WEAPON_REDSHURIKEN_MAX_DISTANCEX, dx);
		}
		vx += WEAPON_REDSHURIKEN_REVERSE_ACCELERATEX;

		if (this->isReverse)
		{
			dy += WEAPON_REDSHURIKEN_REVERSE_DISTANCEY;
		}
		else dy -= WEAPON_REDSHURIKEN_REVERSE_DISTANCEY;
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