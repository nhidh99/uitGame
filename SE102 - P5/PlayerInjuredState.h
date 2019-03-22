#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerInjuredState : public PlayerState
{
private:
	bool _isReverse;

public:
	PlayerInjuredState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard() {};
	State GetName();
};