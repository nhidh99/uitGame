#pragma once
#include "Enemy.h"
#include "ObjectItemDagger.h"


class EnemyCloakMan : public Enemy {
public:
	ObjectItemDagger* dagger;
	EnemyCloakMan();
	~EnemyCloakMan();

	void Render(float translateX = 0, float translateY = 0);
	void Update(float dt);
};