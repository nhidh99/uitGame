#pragma once
#include "Enemy.h"

class EnemyEagle :public Enemy {
public:
	EnemyEagle();
	~EnemyEagle();
};


// dx = vx * dt;
// deltaX = eagle->x  - player->x
// deltaY = ...
// if (deltaX * deltaY > 0) ...
// else ...