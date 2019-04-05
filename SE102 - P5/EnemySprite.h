#pragma once
#include"Sprite.h"

class EnemySprite :public Sprite {
public:
	EnemyType _type;
	EnemySprite() {};
	EnemySprite(EnemyType type, int left, int top, int right, int bottom);
	EnemyType GetType();
};