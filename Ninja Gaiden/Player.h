#pragma once
#include "Object.h"
#include "PlayerSprite.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "ObjectItemSword.h"
#include <unordered_set>
#include <map>
#include <set>

class Player : public Object
{
private:
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;
	
	Rect curGroundBound, curWallBound;
	bool DetectGround(std::unordered_set<Rect*> grounds);
	bool DectectWall(std::unordered_set<Rect*> walls);
	
public:
	Player();
	~Player();
	static Player* GetInstance();

	PlayerState* state;
	State stateName; 
	Animation* curAnimation;								// Animation hiện tại
	ObjectItemSword* sword;
	ObjectItem* item;							
	std::unordered_map<State, bool> allow;

	void Update(float dt, std::vector<Object*> ColliableObjects);
	void CheckGroundCollision(std::unordered_set<Rect*> grounds);
	void CheckWallCollision(std::unordered_set<Rect*> walls);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);							
	void OnKeyUp(int keyCode);							
	void ChangeState(PlayerState* newState);				
	void AttackWith(Type item);
};