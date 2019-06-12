#pragma once
#include "Weapon.h"

class WeaponRedShuriken : public Weapon
{
private:
	bool isOut;

public:
	WeaponRedShuriken();
	~WeaponRedShuriken() {}
	void UpdateDistance(float dt);
};