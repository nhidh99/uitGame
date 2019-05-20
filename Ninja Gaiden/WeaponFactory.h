#pragma once
#include "WeaponBlueShuriken.h"

class WeaponFactory
{
public:
	static Weapon* CreateWeapon(int weaponID)
	{
		switch (weaponID)
		{
		case 1:
			return new WeaponBlueShuriken();
		default:
			return NULL;
		}
	}

	static Weapon* ConvertToWeapon(Object* obj)
	{
		Weapon* w = (Weapon*)obj;

		switch (w->type)
		{
		case BLUESHURIKEN:
			w = (WeaponBlueShuriken*)w;
			break;
		}

		return w;
	}
};