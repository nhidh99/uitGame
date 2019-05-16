
#pragma once
#include "Object.h"
#include "EnemySprite.h"
#include "Cell.h"
#include <algorithm>

class Enemy : public Object
{
protected:
	Animation* curAnimation;
	std::unordered_map<State, Animation*> animations;

public:
	Enemy()
	{
		tag = ENEMY;
		animations[DEAD] = new Animation(WEAPON, 0, 2, 85);
	}

	~Enemy() {};
	State StateName;
	Type type;
	bool isActive;
	bool isDead;

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

	virtual void Update(float dt)
	{
		if (this->isActive)
		{
			curAnimation->Update(dt);
			dx = vx * dt;
			dy = vy * dt;
		}

		if (this->StateName == DEAD)
		{
			this->dx = this->dy = 0;
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