#pragma once
#pragma once
#include "ObjectItem.h"


class ObjectItemDagger : public ObjectItem
{
private:
	Sprite* sprite;
public:
	ObjectItemDagger();
	~ObjectItemDagger();
	void Update(float dt,int maxHight, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};