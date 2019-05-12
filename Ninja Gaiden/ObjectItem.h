#pragma once
#include "Object.h"
#include "Enemy.h"
#include <unordered_set>
#include <map>

class ObjectItem : public Object
{
public:
	ObjectItem() {}
	Type type;
	bool isOnScreen;

	virtual void Update(float dt) {};			// Update thông số của Object sau khoảng thời gian delta-time
	//virtual void Update(float dt, int leftScreen, int rightScreen) {};
	virtual void Render(float translateX = 0, float translateY = 0) {};
	virtual void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		for (auto obj : ColliableObjects)
		{
			if (obj->tag == ENEMY)
			{
				if (this->GetRect().IsContain(obj->GetRect()))
				{
					auto e = (Enemy*)obj;
					e->ChangeState(DEAD);
				}
			}
		}
	}
};