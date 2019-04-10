#pragma once
#include "Object.h"
#include "SceneManager.h"
#include "PlayerSprite.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "ObjectItemSword.h"
#include "ObjectItemSwingSword.h"
#include <map>

class Player : public Object
{
private:
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;

	bool IsOnGround(BoundingBox ground);
	bool DetectGround(std::vector<BoundingBox> grounds);
	bool DectectWall(std::vector<BoundingBox> walls);

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
	BoundingBox curGroundBound, curWallBound;
	std::unordered_map<State, bool> allow;

	void Update(float dt, std::vector<Object*> ColliableObjects);
	void CheckOnGround(std::vector<BoundingBox> grounds);
	void CheckOnWall(std::vector<BoundingBox> walls);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void ChangeState(PlayerState* newState);
	void AttackWith(Type item);
};