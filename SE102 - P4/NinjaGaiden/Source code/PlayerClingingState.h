#pragma once
#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingingState : public PlayerState
{
public:
	PlayerClingingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard(std::map<int, bool> keyCode);
	State GetName();
};