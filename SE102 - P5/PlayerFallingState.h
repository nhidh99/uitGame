#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerFallingState : public PlayerState
{
private:
	float _fallingSpeed;
	bool _reverse;

public:
	PlayerFallingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard();
};