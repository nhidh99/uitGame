#pragma once
#include "Weapon.h"

class WeaponShuriken : public Weapon
{
private:
	Sprite *_sprite;

public:
	WeaponShuriken();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};