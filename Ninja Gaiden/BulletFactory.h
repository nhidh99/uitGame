#pragma once
#include "BulletCloakMan.h"
#include "BulletGunMan.h"

class BulletFactory
{
public:
	static Bullet* CreateBullet(Type bulletType)
	{
		switch (bulletType)
		{
		case CLOAKMAN: return new BulletCloakMan();
		case GUNMAN: return new BulletGunMan();
		}
	}

	static Bullet* ConvertToBullet(Object* o)
	{
		Bullet* b = (Bullet*)o;

		switch (o->type)
		{
		case CLOAKMAN:
			b = (BulletCloakMan*)b;
			break;
		
		case GUNMAN:
			b = (BulletGunMan*)b;
			break;
		}
		return b;
	}
};