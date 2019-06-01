#pragma once
#include"Enemy.h"

class EnemyRunMan : public Enemy
{
public:
	EnemyRunMan();
	void UpdateDistance(float dt);
};