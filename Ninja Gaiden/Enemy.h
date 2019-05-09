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
		isActive = false;
	}
	
	~Enemy() {};
	Type type;
	bool isActive;

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
	}

	bool IsRespawnOnScreen()
	{
		return Rect(spawnX - (width >> 1), spawnY - (height >> 1), width, height).IsContain(camera->GetRect());
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