#pragma once
#include "Object.h"
#include <map>

class Item : public Object
{
public:
	Item() {};
	virtual void Update(float dt);
	virtual void Reverse(bool flag);
	virtual void Render();
	virtual void OnKeyDown(std::map<int, bool> keyCode) = 0;
	virtual void OnKeyUp(std::map<int, bool>keyCode) = 0;
};