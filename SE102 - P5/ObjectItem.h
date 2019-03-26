#pragma once
#include "Object.h"
#include <map>

class ObjectItem : public Object
{
public:
	ObjectItem() {}
	bool isOnScreen;
	Type type;

	virtual void Update(float dt) = 0;			// Update thông số của Object sau khoảng thời gian delta-time
	virtual void Render(float translateX = 0, float translateY = 0) {};
};