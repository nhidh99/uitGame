#pragma once
#include "Enemy.h"

class EnemyCloakMan : public Enemy 
{
private:
	float delayTime;

public:
	EnemyCloakMan();
	void UpdateDistance(float dt);
	void Update(float dt);
};