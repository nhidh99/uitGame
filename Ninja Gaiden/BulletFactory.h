#pragma once
#include "BulletCloakMan.h"
#include "BulletGunMan.h"
#include "BulletBazokaMan.h"
#include "BulletBoss.h"

class BulletFactory
{
public:
	static Bullet* CreateBullet(Type bulletType)
	{
		switch (bulletType)
		{
		case CLOAKMAN: return new BulletCloakMan();
		case GUNMAN: return new BulletGunMan();
		case BAZOKAMAN: return new BulletBazokaMan();
		case BOSS: return new BulletBoss();
		}
	}
};