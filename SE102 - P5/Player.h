﻿#pragma once
#include "Object.h"
#include "PlayerSprite.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "ObjectItemSword.h"
#include "ObjectItemSwingSword.h"
#include "ObjectGround.h"
#include <map>

class Player : public Object
{
private:
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;
	bool IsOnGround(BoundingBox ground);
	BoundingBox DetectGround(std::vector<BoundingBox> grounds);

public:
	Player();
	~Player();
	static Player* GetInstance();
	PlayerState* state;

	bool isLastFrame;
	State stateName; 
	Animation* curAnimation;								// Animation hiện tại
	ObjectItemSword* sword;
	ObjectItem* item;							
	BoundingBox curGroundBound;
	std::unordered_map<State, bool> allow;

	void Update(float dt, std::vector<Object*> ColliableObjects);
	void CheckOnGround(std::vector<BoundingBox> grounds);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);							
	void OnKeyUp(int keyCode);							

	void ChangeState(PlayerState* newState);				
	void AttackWith(Type item);
};