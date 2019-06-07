#pragma once
#include"Enemy.h"

class EnemyPanther :public Enemy 
{
private:
	Rect curGroundBound;

public:
	float activeDistance;
	bool isOnGround;
	EnemyPanther();
	~EnemyPanther();
	void DetectGround(std::unordered_set<Rect*> grounds);
	void DetectCurGround(std::unordered_set<Rect*> grounds);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};