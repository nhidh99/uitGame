#pragma once
#include "Object.h"
#include "PlayerSprite.h"
#include "PlayerHandler.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "ObjectItemSword.h"
#include "ObjectItemSwingSword.h"
#include <map>

class Player : public Object
{
private:
	PlayerHandler* _playerHandler;							// PlayerHandler - trung gian giữa Player và PlayerState
	Animation* _curAnimation;								// Animation hiện tại
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State

public:
	Player();
	~Player();

	bool isLastFrame;
	State state;
	ObjectItemSword* sword;
	ObjectItemSwingSword* swingSword;
	ObjectItem* item;										// Item đang giữ để ném
	std::unordered_map<State, bool> allow;

	void Update(float dt);
	void Render();
	void OnKeyDown(int keyCode);							// Xử lí sự kiện của nhân vật theo phím nhấn
	void OnKeyUp(int keyCode);								// Xử lí sự kiện của nhân vật theo phím thả

	void ChangeState(PlayerState* newState);				// Đổi State
	void AttackWith(Type item);
};