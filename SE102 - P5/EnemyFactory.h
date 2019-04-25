#pragma once
#include "Enemy.h"
#include "EnemySwordMan.h"
#include "EnemyGunMan.h"
#include "EnemyCloakMan.h"
#include "EnemyEagle.h"
#include "EnemyPanther.h"
class EnemyFactory {
public:
	Enemy* enemy;

	EnemyFactory() {};
	~EnemyFactory() {};

	Enemy* CreateEnemy(int type) {
		switch (type) 
		{
		case 1:
			return new EnemySwordMan();
		case 2:
			return new EnemyGunMan();
		case 3:
			return new EnemyPanther();
		case 4:
			return new EnemyEagle();
		case 5:
			return new EnemyCloakMan();
		default:
			return NULL;
		}
	}
};