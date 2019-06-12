#pragma once
#include "Object.h"
#include "Camera.h"
#include <unordered_set>
#include "Sound.h"

class Bullet : public Object
{
protected:
	Animation* activeAnimation;
	Animation* deadAnimation;
	Animation* curAnimation;

public:
	State StateName;

	Bullet()
	{
		this->tag = BULLET;
		deadAnimation = new Animation(WEAPON, 0, 2, 85);
	}

	~Bullet()
	{
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY + SCREEN_TRANSLATEY);
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt)
	{
		if (isFrozenEnemies)
		{
			this->dx = this->dy = 0;
		}
		else
		{
			this->UpdateDistance(dt);
			curAnimation->Update(dt);
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
			}
		}
	}

	void ChangeState(State StateName)
	{
		this->StateName = StateName;

		switch (StateName)
		{
		case ACTIVE:
		{
			curAnimation = activeAnimation;
			this->isDead = false;
			break;
		}

		case DEAD:
		{
			curAnimation = deadAnimation;
			Sound::getInstance()->play("enemydie");
			break;
		}
		}
	}
};