#pragma once
#include"Sprite.h"

class EnemySprite : public Sprite 
{
public:
	Type type;
	EnemySprite() {};
	EnemySprite(Type type, int left, int top, int right, int bottom);
};