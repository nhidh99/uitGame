#pragma once
#include "Weapon.h"

class WeaponSword : public Weapon
{
public:
	WeaponSword();
	void Update(float dt);
	void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		if (this->isOnScreen)
		{
			Weapon::Update(dt, ColliableObjects);
		}
	}
	void Render(float x, float y, int frameIndex, float translateX = 0, float translateY = 0);
};