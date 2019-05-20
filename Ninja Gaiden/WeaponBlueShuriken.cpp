#include "WeaponBlueShuriken.h"

WeaponBlueShuriken::WeaponBlueShuriken()
{
	animation = new Animation(WEAPON, 5, 6);
	isOnScreen = false;
	width = WEAPON_BLUESHURIKEN_WIDTH;
	height = WEAPON_BLUESHURIKEN_HEIGHT;
	vx = WEAPON_BLUESHURIKEN_SPEED;
	vy = 0;
	type = BLUESHURIKEN;
}

WeaponBlueShuriken::~WeaponBlueShuriken()
{
}

void WeaponBlueShuriken::Update(float dt, std::unordered_set<Object*> ColliableObjects)
{
	dx = vx * dt;
	dy = vy * dt;
	animation->Update(dt);

	for (auto obj : ColliableObjects)
	{
		if (this->GetRect().IsContain(obj->GetRect()))
		{
			if (obj->tag == ENEMY)
			{
				auto e = (Enemy*)obj;
				e->ChangeState(DEAD);
				this->isDead = true;
				break;
			}

			else if (obj->tag == HOLDER)
			{
				auto h = (Holder*)obj;
				h->isDead = true;
				this->isDead = true;
				break;
			}
		}
	}
}
