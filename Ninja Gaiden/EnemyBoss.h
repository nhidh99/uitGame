#pragma once
#include "Enemy.h"

class EnemyBoss : public Enemy
{
private:
	bool firstJump;
	int explodeTimes;
	float delayTime;
	float delayDead;

public:
	int bulletCountdown;
	EnemyBoss();
	~EnemyBoss() {};
	void UpdateDistance(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
	void Render(float translateX = 0, float translateY = 0);
};