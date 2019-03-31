#pragma once
#include "Object.h"
#include "PlayerSprite.h"
#include "PlayerHandler.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "ObjectItemSword.h"
#include "ObjectItemSwingSword.h"
#include "ObjectGround.h"
#include <map>

class Player : public Object
{
private:
	PlayerHandler* _playerHandler;							// PlayerHandler - trung gian giữa Player và PlayerState
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State
	bool IsOnGround();

public:
	Player();
	~Player();

	bool isLastFrame;
	State state; 
	Animation* curAnimation;								// Animation hiện tại
	ObjectItemSword* sword;
	ObjectItem* item;										// Item đang giữ để ném
	BoundingBox curGroundBound;
	std::unordered_map<State, bool> allow;

	void Update(float dt, std::vector<Object*> ColliableObjects);
	void CheckOnGround(std::vector<ObjectGround*> grounds);
	void CheckOnGround(std::vector<BoundingBox> grounds);
	void Render(float translateX = 0, float translateY = 0);
	void OnKeyDown(int keyCode);							// Xử lí sự kiện của nhân vật theo phím nhấn
	void OnKeyUp(int keyCode);								// Xử lí sự kiện của nhân vật theo phím thả

	void ChangeState(PlayerState* newState);				// Đổi State
	void AttackWith(Type item);
};