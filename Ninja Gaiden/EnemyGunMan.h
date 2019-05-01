#pragma once
#include "Enemy.h"
#include "ObjectItemBullet.h"

class EnemyGunMan : public Enemy {
public:
	ObjectItemBullet* bullet;
	EnemyGunMan();
	~EnemyGunMan();
	void Update(float dt);
	void Render(float translateX = 0, float translateY = 0);
};