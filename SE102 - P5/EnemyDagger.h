#pragma once
#pragma once
#include "ObjectItem.h"


class EnemyDagger : public ObjectItem
{
private:
	Sprite* sprite;
public:
	int maxHigh;
	EnemyDagger();
	~EnemyDagger();
	void Update(float dt, int leftScreen, int rightScreen);
	void Render(float translateX = 0, float translateY = 0);
};