#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"

class PlayerRunningState : public PlayerState
{
private:
	float _runningSpeed;

public:
	PlayerRunningState(PlayerHandler* playerHandler);
	void Update(float dt) {};
	void HandleKeyboard(std::map<int, bool> keyCode);
	State GetName();
};