#pragma once
#include "Object.h"
#include <map>

class ObjectItem : public Object
{
protected:
	Animation* _animation;				// Animation của Object
	bool _isOnScreen;					// Kiểm tra Object có xuất hiện trên màn hình

public:
	ObjectItem() {}
	virtual void OnScreen(bool flag);
	virtual void Update(float dt) = 0;
	virtual void Render();
	virtual bool IsOnScreen();
};