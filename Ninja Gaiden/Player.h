﻿#pragma once
#include "PlayerSprite.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerInjuredState.h"
#include "ItemFactory.h"
#include "Enemy.h"
#include <unordered_set>

class Player : public Object
{
private:
	std::unordered_map<State, Animation*> animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;
	
	Rect curGroundBound, curWallBound;
	bool DetectGround(std::unordered_set<Rect*> grounds);
	bool DectectWall(std::unordered_set<Rect*> walls);
	
public:
	Player();
	~Player();
	static Player* GetInstance();

	bool isOnGround, isThrowing, isAttacking;
	PlayerState* state;
	State stateName;
	Animation* curAnimation;								// Animation hiện tại
	Type weaponType;
	std::unordered_map<State, bool> allow;

	void Update(float dt, std::unordered_set<Object*> ColliableObjects);
	void CheckGroundCollision(std::unordered_set<Rect*> grounds);
	void CheckWallCollision(std::unordered_set<Rect*> walls);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);							
	void OnKeyUp(int keyCode);							
	void ChangeState(PlayerState* newState);
};