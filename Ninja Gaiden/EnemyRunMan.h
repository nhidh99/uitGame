#pragma once
#include"Enemy.h"

class EnemyRunMan : public Enemy
{
private:
	Rect curGroundBound;

public:
	bool isOnGround;
	float activeDistance;
	EnemyRunMan();
	void DetectCurGround(std::unordered_set<Rect*> grounds);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};