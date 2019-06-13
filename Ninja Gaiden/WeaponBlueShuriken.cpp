#include "WeaponBlueShuriken.h"

WeaponBlueShuriken::WeaponBlueShuriken()
{
	animation = new Animation(WEAPON, 5, 6);
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
	Object::Update(dt);
	animation->Update(dt);

	for (auto obj : ColliableObjects)
	{
		if (this->GetRect().IsContain(obj->GetRect()))
		{
			switch (obj->tag)
			{
			case BULLET:
			{
				auto b = (Bullet*)obj;
				if (b->StateName != DEAD)
				{
					b->ChangeState(DEAD);
					this->isDead = true;
					break;
				}
			}

			case ENEMY:
			{
				if (obj->type != BOSS)
				{
					auto e = (Enemy*)obj;
					e->ChangeState(DEAD);
				}
				else
				{
					auto e = (EnemyBoss*)obj;
					e->SubtractHealth();
				}
				this->isDead = true;
				break;
			}

			case HOLDER:
			{
				auto h = (Holder*)obj;
				h->isDead = true;
				this->isDead = true;
				break;
			}
			}

			if (this->isDead) return;
		}
	}
}
