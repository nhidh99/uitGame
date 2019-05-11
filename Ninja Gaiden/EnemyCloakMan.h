#pragma once
#include "Enemy.h"
#include "EnemyDagger.h"


class EnemyCloakMan : public Enemy {
public:
	EnemyDagger* dagger;
	EnemyCloakMan();
	~EnemyCloakMan();

	void Render(float translateX = 0, float translateY = 0);
	void Update(float dt, Rect camRect);
};