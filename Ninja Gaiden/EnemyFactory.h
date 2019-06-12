#pragma once
#include "Enemy.h"
#include "EnemySwordMan.h"
#include "EnemyGunMan.h"
#include "EnemyCloakMan.h"
#include "EnemyEagle.h"
#include "EnemyPanther.h"
#include "EnemyBazokaMan.h"
#include "EnemyRunMan.h"
#include "EnemyBoss.h"

class EnemyFactory
{
public:
	EnemyFactory() {};
	~EnemyFactory() {};

	static Enemy* CreateEnemy(int enemyID)
	{
		switch (enemyID)
		{
		case 1: return new EnemySwordMan();
		case 2: return new EnemyGunMan();
		case 3: return new EnemyPanther();
		case 4: return new EnemyEagle();
		case 5: return new EnemyCloakMan();
		case 6: return new EnemyBazokaMan();
		case 7: return new EnemyRunMan();
		case 8: return new EnemyBoss();
		default: return NULL;
		}
	}
};