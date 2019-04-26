#pragma once
#include "ObjectItem.h"

class ObjectItemBullet : public ObjectItem
{
private:
	Sprite* sprite;
public:
	ObjectItemBullet();
	~ObjectItemBullet();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};