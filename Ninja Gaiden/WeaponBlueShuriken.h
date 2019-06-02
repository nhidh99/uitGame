#pragma once
#include "Weapon.h"

class WeaponBlueShuriken : public Weapon
{
public:
	WeaponBlueShuriken();
	~WeaponBlueShuriken();
	void Update(float dt, std::unordered_set<Object*> ColliableObjects);
};