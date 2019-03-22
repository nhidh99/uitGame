#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard();
};