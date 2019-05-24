#pragma once
#include "Enemy.h"
#include "WeaponDagger.h"

class EnemyCloakMan : public Enemy 
{
private:
	float distance;

public:
	EnemyCloakMan();
	~EnemyCloakMan();
	void UpdateDistance(float dt);
	void Update(float dt);
};