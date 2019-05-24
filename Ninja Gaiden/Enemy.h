#pragma once
#include "Player.h"
#include "EnemySprite.h"
#include "Cell.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Enemy : public Object
{
protected:
	std::unordered_map<State, Animation*> animations;
	Animation* curAnimation;
	Rect groundBound;

public:
	State StateName;
	Type type;
	bool isActive;
	bool isDead;

	Enemy()
	{
		tag = ENEMY;
		animations[DEAD] = new Animation(WEAPON, 0, 2, 85);
	}

	void DectectGround(std::unordered_set<Rect*> grounds)
	{
		for (auto g : grounds)
		{
			if (g->x < this->posX && this->posX < g->x + g->width && g->y >= groundBound.y)
			{
				groundBound = *g;
			}
		}
		this->posY = groundBound.y + groundBound.height + (this->width>>1);
	}

	~Enemy() 
	{
		if (curAnimation) delete curAnimation;
	};

	void Render(float translateX = 0, float translateY = 0)
	{
		if (this->isActive)
		{
			auto posX = this->posX + translateX;
			auto posY = this->posY + translateY;
			camera->ConvertPositionToViewPort(posX, posY);
			curAnimation->isReverse = this->isReverse;
			curAnimation->Render(posX, posY);
		}
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt)
	{
		if (this->isActive)
		{
			if (isFrozenEnemies)
			{
				this->dx = this->dy = 0;
			}
			else 
			{
				curAnimation->Update(dt);
				this->UpdateDistance(dt);
			}
		}

		if (this->StateName == DEAD)
		{
			this->dx = this->dy = 0;

			if (isFrozenEnemies)
			{
				curAnimation->Update(dt);
			}

			if (curAnimation->isLastFrame)
			{
				this->isDead = true;
				this->isActive = false;
			}
		}
	}

	bool IsRespawnOnScreen()
	{
		return Rect(spawnX - (width >> 1), spawnY - (height >> 1), width, height).IsContain(camera->GetRect());
	}

	void ChangeState(State StateName)
	{
		switch (StateName)
		{
		case DEAD:
		{
			break;
		}
		default:
		{
			this->isActive = true;
			this->isDead = false;
			break;
		}
		}
		this->StateName = StateName;
		this->curAnimation = animations[StateName];
	}
};