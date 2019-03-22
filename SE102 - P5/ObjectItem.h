#pragma once
#include "Object.h"
#include <map>

class ObjectItem : public Object
{
public:
	ObjectItem() {}
	bool isOnScreen;
	Type type;
	virtual void Update(float dt) = 0;
	virtual void Render() {};
};