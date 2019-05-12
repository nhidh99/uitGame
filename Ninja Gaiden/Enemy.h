
#pragma once
#include "Object.h"
#include "EnemySprite.h"
#include "Cell.h"
#include <algorithm>

class Enemy : public Object
{
protected:
	float deadX, deadY;
	Animation* curAnimation;
	std::unordered_map<State, Animation*> animations;

public:
	Enemy()
	{
		tag = ENEMY;
	}

	~Enemy() {};
	Type type;
	bool isActive;
	bool isDead;

	void Render(float translateX = 0, float translateY = 0)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

	virtual void Update(float dt)
	{
		if (this->isActive)
		{
			curAnimation->Update(dt);
			dx = vx * dt;
			dy = vy * dt;
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
			this->isDead = true;
			this->isActive = false;
			break;
		}
		default:
		{
			this->isActive = true;
			this->isDead = false;
			this->curAnimation = animations[StateName];
			break;
		}
		}
	}
};