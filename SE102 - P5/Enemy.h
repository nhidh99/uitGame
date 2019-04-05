#pragma once
#include"Object.h"
#include"EnemySprite.h"

class Enemy : public Object {
public:
	Animation* _animation;
	EnemySprite* _sprite;

	Enemy() {};
	~Enemy() {};
	void Render() {};
	void Render(float translateX = 0, float translateY = 0);
	void Update(float dt) {};
	void Reverse() {};
};