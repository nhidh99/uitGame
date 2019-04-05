#pragma once
#include"Enemy.h"


class SwordMan :public Enemy{
public:
	Animation* animation;
	EnemyType type;
	EnemySprite* deadSprite;

	RECT GetBound();

	SwordMan();
	~SwordMan();

	void Render();
	void Render(float translateX = 0, float translateY = 0);
	void Update(float dt);

	bool IsLastFrame();
};