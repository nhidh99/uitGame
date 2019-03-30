#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerAttackingState : public PlayerState
{
private:
	State _curState;				// Biến tạm dùng xét State sẽ chuyển đổi sau khi thoát State
	State _attackState;				// Loại ATTACK_STATE (vì khi nhấn sẽ có 2 loại ATTACK là SIT và STAND)
	bool _reverse;

public:
	PlayerAttackingState(PlayerHandler* playerHandler);
	~PlayerAttackingState();
	void Update(float dt);
	void HandleKeyboard(std::map<int, bool> keyCode);
	State GetName();
};