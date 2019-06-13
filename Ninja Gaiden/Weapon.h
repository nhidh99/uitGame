#pragma once
#include "Player.h"
#include "EnemyBoss.h"
#include "Holder.h"
#include "ScoreBoard.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	Animation* animation;

public:
	Weapon()
	{
		tag = WEAPON;
		if (player->isThrowing)
		{
			player->allow[THROWING] = false;
		}
	}

	~Weapon()
	{
		if (type != SWORD)
		{
			player->allow[THROWING] = true;
		}
	}

	virtual void Update(float dt) {};			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		animation->Render(posX, posY+ SCREEN_TRANSLATEY);
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

		auto rect = this->GetRect();

		for (auto obj : ColliableObjects)
		{
			if (rect.IsContain(obj->GetRect()))
			{
				switch (obj->tag)
				{
				case BULLET:
				{
					auto b = (Bullet*)obj;
					b->ChangeState(DEAD);
					break;
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
						this->isDead = true;
					}
					break;
				}

				case HOLDER:
				{
					auto h = (Holder*)obj;
					h->isDead = true;
					break;
				}
				}
			}
		}
	}
};