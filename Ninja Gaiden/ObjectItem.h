#pragma once
#include "Object.h"
#include <map>

class ObjectItem : public Object
{
public:
	ObjectItem() {}
	Type type;
	bool isOnScreen;

	virtual void Update(float dt) {};			// Update thông số của Object sau khoảng thời gian delta-time
	virtual void Update(float dt, int leftScreen, int rightScreen) {};
	virtual void Render(float translateX = 0, float translateY = 0) {};
};