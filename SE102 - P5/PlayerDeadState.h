#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerDeadState : public PlayerState
{
public:
	PlayerDeadState();
	void Update(float dt) {};
	void HandleKeyboard() {};
	State GetName();
};