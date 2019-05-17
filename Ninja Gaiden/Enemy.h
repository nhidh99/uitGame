#pragma once
#include "Object.h"
#include "EnemySprite.h"
#include "Cell.h"
#include "Math.h"
#include <algorithm>
#include "GameGlobal.h"
#include "Player.h"

class Enemy : public Object
{
//protected:
//	Animation* curAnimation;
//	std::unordered_map<State, Animation*> animations;
//
public:
	Enemy() { tag = ENEMY; }
	~Enemy() {};

	Type type;
	bool isActive;
	float spawnX, spawnY;
	float moveSpaceHead, moveSpaceTail;
	Animation* curAnimation;
	std::unordered_map<State, Animation*> animations;

	void Render()
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

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
		curAnimation->Update(dt);
		dx = vx * dt;
		dy = vy * dt;

		////Xét phạm vi hoạt động của enemy
		//if (this->posX > moveSpaceTail)
		//{
		//	this->vx = -vx;
		//	this->isReverse = !this->isReverse;
		//}

		//Xét hướng đi của enemy đối với player
		if (this->posX > player->posX && this->posX < moveSpaceTail)
		{
			if (this->vx > 0)
			{
				this->vx = -vx;
			}

			if (!this->isReverse)
			{
				this->isReverse = true;
			}
		}
		if (this->posX < player->posX && this->posX < moveSpaceTail)
		{
			if (this->vx < 0)
			{
				this->vx = -vx;
			}
			this->isReverse = false;
		}
			
	}

	bool IsRespawnOnScreen(Rect CameraRect)
	{
		return Rect(spawnX - (width >> 1), spawnY - (height >> 1), width, height).IsContain(CameraRect);
	}

	/*std::unordered_set<Cell*> GetContainedCells()
	{
		std::unordered_set<Cell*> cells;
		auto r = GetRect();
		int left = r.x / Cell::width;
		int right = (r.x + r.width) / Cell::width;
		int top = r.y / Cell::height;
		int bottom = (r.y + r.height) / Cell::height;
		cells.insert()
	}*/
};