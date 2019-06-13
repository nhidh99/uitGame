#pragma once
#include "Enemy.h"
#include "ScoreBoard.h"

class EnemyBoss : public Enemy
{
private:
	bool firstJump;
	int health;
	int explodeTimes;
	float delayJump;
	float delayDead;
	float delayHit;

public:
	int bulletCountdown;

	EnemyBoss();
	~EnemyBoss() {};
	void UpdateDistance(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
	void SubtractHealth();
	void Render(float translateX = 0, float translateY = 0);
};