#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"

class EnemyGunMan : public Enemy {
public:
	EnemyBullet* bullet;
	std::vector<EnemyBullet*> bullets;
	EnemyGunMan();
	~EnemyGunMan();
	void Update(float dt, Rect camRect);
	void Render(float translateX = 0, float translateY = 0);
};