#pragma once
#include"Enemy.h"

class EnemyPanther :public Enemy 
{
public:
	EnemyPanther();
	~EnemyPanther();
	void UpdateDistance(float dt);
};