#pragma once
#include "Enemy.h"
#include "Math.h"


class EnemyEagle :public Enemy {
public:
	float reversePointX,reversePointY;
	float maxDepth, maxHigh;

	EnemyEagle();
	~EnemyEagle();

	void Update(float dt);
};