#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"

class PlayerJumpingState : public PlayerState
{
private:
	float _jumpingSpeed;
	bool _reverse;

public:
	PlayerJumpingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard();
};