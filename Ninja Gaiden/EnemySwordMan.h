#pragma once
#include "Enemy.h"

class EnemySwordMan : public Enemy
{
public:
	EnemySwordMan();
	~EnemySwordMan();
	void UpdateDistance(float dt);
};