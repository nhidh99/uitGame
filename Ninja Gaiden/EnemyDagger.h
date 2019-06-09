#pragma once
#pragma once
#include "ObjectItem.h"


class EnemyDagger : public ObjectItem
{
private:
	Sprite* sprite;
public:
	float maxHigh;
	EnemyDagger();
	~EnemyDagger();
	void Update(float dt);
	void Render(float translateX = 0, float translateY = 0);
	bool isOutCam(Rect camRect);
};