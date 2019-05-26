#pragma once
#include "Enemy.h"
#include "EnemySwordMan.h"
#include "EnemyGunMan.h"
#include "EnemyCloakMan.h"
#include "EnemyEagle.h"
#include "EnemyPanther.h"

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
		default: return NULL;
		}
	}

	static Enemy* ConvertToEnemy(Object* o)
	{
		Enemy* e = (Enemy*)o;

		switch (o->type)
		{
		case SWORDMAN:
		{
			e = (EnemySwordMan*)o;
			break;
		}

		case GUNMAN:
		{
			e = (EnemyGunMan*)o;
			break;
		}

		case PANTHER:
		{
			e = (EnemyPanther*)o;
			break;
		}

		case EAGLE:
		{
			e = (EnemyEagle*)o;
			break;
		}

		case CLOAKMAN:
		{
			e = (EnemyCloakMan*)o;
			break;
		}
		}
		return e;
	}
};