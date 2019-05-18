#pragma once
#include "Weapon.h"

class WeaponSwingSword : public Weapon
{
private:
	Animation *_animation;

public:
	WeaponSwingSword();
	void Update(float dt);
	void Render(float x, float y, int frameIndex, float translateX, float translateY);
};