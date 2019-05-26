#pragma once
#define _USE_MATH_DEFINES
#include "Enemy.h"
#include <ctime>
#include <stdlib.h>

class EnemyEagle : public Enemy 
{
private:
	float delayTime;

public:
	EnemyEagle();
	~EnemyEagle();
	void UpdateDistance(float dt);
	void Update(float dt);
};