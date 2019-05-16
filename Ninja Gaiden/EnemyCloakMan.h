#pragma once
#include "Enemy.h"
#include "WeaponDagger.h"


class EnemyCloakMan : public Enemy {
public:
	WeaponDagger* dagger;
	EnemyCloakMan();
	~EnemyCloakMan();

	void Render(float translateX = 0, float translateY = 0);
	void Update(float dt);
};