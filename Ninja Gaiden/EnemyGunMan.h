#pragma once
#include "Enemy.h"
#include "WeaponBullet.h"

class EnemyGunMan : public Enemy {
public:
	WeaponBullet* bullet;
	EnemyGunMan();
	~EnemyGunMan();
	void Update(float dt);
	void Render(float translateX = 0, float translateY = 0);
};