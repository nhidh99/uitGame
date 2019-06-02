#pragma once
#include "Weapon.h"

class WeaponFireWheel : public Weapon
{
public:
	WeaponFireWheel()
	{
		animation = new Animation(WEAPON, 7, 10, DEFAULT_TPS >> 4);
		width = WEAPON_FIREWHEEL_WIDTH;
		height = WEAPON_FIREWHEEL_HEIGHT;
		vx = WEAPON_FIREWHEEL_SPEEDX;
		vy = WEAPON_FIREWHEEL_SPEEDY;
		type = FIREWHEEL;
	}
};