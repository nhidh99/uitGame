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
	State _state;											// Trạng thái hiện tại
	ObjectItemSword* _sword;
	ObjectItemSwingSword* _swingsword;		
	ObjectItem* _item;										// Item đang giữ để ném
	PlayerHandler* _playerHandler;							// PlayerHandler - trung gian giữa Player và PlayerState
	Animation* _curAnimation;								// Animation hiện tại
	std::unordered_map<State, Animation*> _animations;		// Danh sách các Animation tương ứng với từng State
	std::unordered_map<State, bool> _allow;

public:
	Player();
	~Player();

	void Update(float dt);
	void Render();
	RECT GetBound();										// Vùng hình chữ nhật bao quanh Player

	void HandleKeyBoard(std::map<int, bool> keyCode);		// Xử lí sự kiện bàn phím theo từng State
	void OnKeyDown(int keyCode);							// Xử lí sự kiện của nhân vật theo phím nhấn
	void OnKeyUp(int keyCode);								// Xử lí sự kiện của nhân vật theo phím thả
	
	void ChangeState(PlayerState* newState);				// Đổi State
	void ChangeAnimation(State state);						// Đổi Animation theo State đang xét
	void ChangeSword(ObjectItemSword* sword);
	void ChangeItem(ObjectItem* newItem);					// Đổi Item
	
	void Allow(State state, bool flag);
	void AttackWithSword();
	void AttackWithSwingSword();
	void AttackWithItem();

	bool IsLastFrame();										// Kiểm tra Animation đã ở frame cuối chưa (dùng cho các trường hợp ATTACK)
	bool IsReverse();
	bool IsAllow(State state);

	ObjectItemSword* GetSword();
	ObjectItemSwingSword* GetSwingSword();
	ObjectItem* GetItem();
};