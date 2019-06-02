#pragma once
#include "WeaponBlueShuriken.h"
#include "WeaponFireWheel.h"

class WeaponFactory
{
public:
	static Weapon* CreateWeapon(int weaponID)
	{
		switch (weaponID)
		{
		case 1:
			return new WeaponBlueShuriken();

		case 2:
			return new WeaponFireWheel();
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

		case FIREWHEEL:
			w = (WeaponFireWheel*)w;
			break;
		}

		return w;
	}
};