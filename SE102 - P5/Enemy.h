#pragma once
#include "Object.h"
#include "EnemySprite.h"

class Enemy : public Object 
{
protected:
	Animation* curAnimation;
	std::unordered_map<State, Animation*> animations;
public:
	bool isActive;
	bool allowAttack;
	Type type;

	Enemy() {};
	~Enemy() {};

	void Render()
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY);
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(posX, posY, translateX, translateY);
	}

	void Update(float dt)
	{
		curAnimation->Update(dt);
		Object::Update(dt);
	}

	void ChangeState(Animation* ani)
	{
		this->curAnimation = ani;
	}
};
