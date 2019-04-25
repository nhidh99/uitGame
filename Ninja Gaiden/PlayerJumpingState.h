#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"

class PlayerJumpingState : public PlayerState
{
private:
	bool _reverse;

public:
	PlayerJumpingState();
	void Update(float dt);
	void HandleKeyboard();
};