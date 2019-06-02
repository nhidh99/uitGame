#pragma once
#include "WeaponBlueShuriken.h"
#include "WeaponFireWheel.h"
#include "WeaponSword.h"

class WeaponFactory
{
public:
	static Weapon* CreateWeapon(Type weaponType)
	{
		switch (weaponType)
		{
		case SWORD:
			return new WeaponSword();

		case BLUESHURIKEN:
			return new WeaponBlueShuriken();

		case FIREWHEEL:
			return new WeaponFireWheel();

		default:
			return NULL;
		}
	}

	static Weapon* ConvertToWeapon(Object* o)
	{
		Weapon* w = (Weapon*)o;

		switch (o->type)
		{
		case SWORD:
			w = (WeaponSword*)w;
			break;

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