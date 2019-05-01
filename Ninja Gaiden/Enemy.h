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
	Enemy() { tag = ENEMY; }
	~Enemy() {};
	Type type;
	float spawnX, spawnY;

	void Render()
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY, translateX, translateY);
	}

	virtual void Update(float dt)
	{
		curAnimation->Update(dt);
		Object::Update(dt);
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