#pragma once
#include "Enemy.h"

class EnemyEagle : public Enemy 
{
private:
	float delayTime;

public:
	float activeDistance;
	EnemyEagle();
	void UpdateDistance(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
};