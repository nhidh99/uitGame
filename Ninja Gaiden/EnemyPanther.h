#pragma once
#include"Enemy.h"

class EnemyPanther :public Enemy {
public:
	EnemyPanther();
	~EnemyPanther();

	void Update(float dt);
};