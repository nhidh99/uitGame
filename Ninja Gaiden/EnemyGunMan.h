#pragma once
#include "Enemy.h"

class EnemyGunMan : public Enemy 
{
private:
	float delayTime;

public:
	EnemyGunMan();
	~EnemyGunMan();
	void UpdateDistance(float dt);
	void Update(float dt);
};