#pragma once
#include "Weapon.h"

class WeaponBullet : public Weapon
{
private:
	Sprite* sprite;
public:
	WeaponBullet();
	~WeaponBullet();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};