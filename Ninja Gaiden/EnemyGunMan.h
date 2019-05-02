#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"

class EnemyGunMan : public Enemy {
public:
	EnemyBullet* bullet;
	EnemyGunMan();
	~EnemyGunMan();
	void Update(float dt);
	void Render(float translateX = 0, float translateY = 0);
};