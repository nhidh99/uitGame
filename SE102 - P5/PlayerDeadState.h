#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerDeadState : public PlayerState
{
public:
	PlayerDeadState(PlayerHandler* playerHandler);
	void Update(float dt) {};
	void HandleKeyboard() {};
	State GetName();
};