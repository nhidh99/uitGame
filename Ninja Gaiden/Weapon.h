#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Holder.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	Animation* animation;

public:
	Weapon() { tag = WEAPON;	}
	~Weapon() { if (animation) delete animation; }

	Type type;
	bool isOnScreen;
	bool isDead;

	virtual void Update(float dt) {};			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		animation->Render(posX, posY);
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		this->UpdateDistance(dt);
		this->posX += dx;
		this->posY += dy;

		animation->isReverse = this->isReverse;
		animation->Update(dt);

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
};