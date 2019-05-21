#pragma once
#include "Weapon.h"

class WeaponSword : public Weapon
{
public:
	WeaponSword()
	{
		animation = new Animation(WEAPON, 3, 4, DEFAULT_TPS >> 1);
		isOnScreen = false;
		width = WEAPON_SWORD_WIDTH;
		height = WEAPON_SWORD_HEIGHT;
		vx = vy = 0;
		type = SWORD;
	}

	void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		for (auto obj : ColliableObjects)
		{
			if (this->GetRect().IsContain(obj->GetRect()))
			{
				if (obj->tag == ENEMY)
				{
					auto e = (Enemy*)obj;
					e->ChangeState(DEAD);
				}

				else if (obj->tag == HOLDER)
				{
					auto h = (Holder*)obj;
					h->isDead = true;
				}
			}
		}
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		auto frameIndex = player->curAnimation->CurFrameIndex - 1;
		auto sprite = animation->GetSprite(frameIndex);
		auto x = player->posX;
		auto y = player->posY + 10;
		sprite->isReverse = this->isReverse;

		switch (frameIndex)
		{
		case 0:
			x += (isReverse ? -22 : 22);
			break;

		case 1:
			x += (isReverse ? -18 : 18);
			this->isDead = true;
			break;
		}

		camera->ConvertPositionToViewPort(x, y);
		sprite->Render(x, y);
	}
};