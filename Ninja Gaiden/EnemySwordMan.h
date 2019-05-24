#pragma once
#include"Enemy.h"

class EnemySwordMan : public Enemy
{
private:
	float distance;

public:
	EnemySwordMan();
	~EnemySwordMan();
	void UpdateDistance(float dt);
};