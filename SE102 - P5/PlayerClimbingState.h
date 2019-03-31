#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClimbingState : public PlayerState
{
public:
	PlayerClimbingState();
	void Update(float dt);
	void HandleKeyboard();
};