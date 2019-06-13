#pragma once
#include "Player.h"
#include "EnemySprite.h"
#include "Cell.h"
#include "Sound.h"
#include "ScoreBoard.h"
#include <algorithm>

class Enemy : public Object
{
protected:
	std::unordered_map<State, Animation*> animations;
	Animation* curAnimation;
	Rect groundBound;

public:
	float speed;
	State StateName;
	bool isActive, isOutScreen;
	int bulletCount;
	int bullets;
	int score;

	Enemy()
	{
		tag = ENEMY;
		isDead = false;
		isActive = false;
		animations[DEAD] = new Animation(WEAPON, 0, 2, 85);
		score = ENEMY_DEFAULT_SCORE;
	}

	~Enemy()
	{
	}

	virtual void DetectGround(std::unordered_set<Rect*> grounds)
	{
		for (auto g : grounds)
		{
			if (g->x < this->posX && this->posX < g->x + g->width
				&& g->y >= groundBound.y && this->posY > g->y)
			{
				groundBound = *g;
			}
		}
		this->spawnY = this->posY = this->groundBound.y + (this->height >> 1);
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
				this->isActive = false;
			}
		}
	}

	Rect GetSpawnRect()
	{
		return Rect(spawnX - (width >> 1), spawnY - (height >> 1), width, height);
	}

	bool IsFinishAttack()
	{
		return (this->StateName == ATTACKING && curAnimation->isLastFrame);
	}

	virtual void ChangeState(State StateName)
	{
		switch (StateName)
		{
		case STANDING:
		{
			this->isOutScreen = false;
			this->isActive = false;
			this->isDead = false;
			break;
		}

		case RUNNING:
		{
			this->isActive = true;
			break;
		}

		case DEAD:
		{
			scoreboard->score += score;
			Sound::getInstance()->play("enemydie");
			break;
		}
		}

		this->StateName = StateName;
		this->curAnimation = animations[StateName];
	}
};