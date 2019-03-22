#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerAttackingState : public PlayerState
{
private:
	State _curState;				// Biến tạm dùng xét State sẽ chuyển đổi sau khi thoát State
	bool _reverse;

public:
	PlayerAttackingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard();
};