#pragma once
#pragma once
#include "Weapon.h"


class WeaponDagger : public Weapon
{
private:
	Sprite* sprite;

public:
	WeaponDagger();
	~WeaponDagger();
	void Update(float dt,int maxHight, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};