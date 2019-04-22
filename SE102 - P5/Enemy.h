#pragma once
#include "Object.h"
#include "EnemySprite.h"
#include "Grid.h"
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

	void Update(float dt, std::vector<std::vector<Cell*>>& cells)
	{
		curAnimation->Update(dt);
		dx = vx * dt;
		dy = vy * dt;

		auto r = this->GetRect();
		int oldLeftCell = r.x / Cell::width;
		int oldRightCell = (r.x + r.width) / Cell::width;
		int oldTopCell = r.y / Cell::height;
		int oldBottomCell = (r.y + r.height) / Cell::height;

		posX += dx;
		posY += dy;

		r = this->GetRect();
		int LeftCell = r.x / Cell::width;
		int RightCell = (r.x + r.width) / Cell::width;
		int TopCell = r.y / Cell::height;
		int BottomCell = (r.y + r.height) / Cell::height;

		if (vx > 0)
		{
			if (LeftCell != oldLeftCell)
			{
				auto objs = &cells[oldTopCell][oldLeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}

				objs = &cells[oldBottomCell][oldLeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}
			}

			if (RightCell != oldRightCell)
			{
				auto objs = &cells[TopCell][RightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}

				objs = &cells[BottomCell][RightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}
			}
		}

		else if (vx < 0)
		{
			if (RightCell != oldRightCell)
			{
				auto objs = &cells[oldTopCell][oldRightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}

				objs = &cells[oldBottomCell][oldRightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}
			}

			if (LeftCell != oldLeftCell)
			{
				auto objs = &cells[TopCell][LeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}

				objs = &cells[BottomCell][LeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}
			}
		}

		if (vy > 0)
		{
			if (TopCell != oldTopCell)
			{
				auto objs = &cells[oldTopCell][oldLeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}

				objs = &cells[oldTopCell][oldRightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}
			}

			if (BottomCell != oldBottomCell)
			{
				auto objs = &cells[BottomCell][RightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}

				objs = &cells[BottomCell][LeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}
			}
		}

		else if (vy < 0)
		{
			if (BottomCell != oldBottomCell)
			{
				auto objs = &cells[oldBottomCell][oldLeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}

				objs = &cells[oldBottomCell][oldRightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) != (*objs).end())
				{
					(*objs).erase(std::remove((*objs).begin(), (*objs).end(), this), (*objs).end());
				}
			}

			if (TopCell != oldTopCell)
			{
				auto objs = &cells[TopCell][RightCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}

				objs = &cells[TopCell][LeftCell]->objects;

				if (std::find((*objs).begin(), (*objs).end(), this) == (*objs).end())
				{
					(*objs).push_back(this);
				}
			}
		}
	}
};