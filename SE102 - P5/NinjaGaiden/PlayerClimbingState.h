#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClimbingState : public PlayerState
{
private:
	float _climbingSpeed;

public:
	PlayerClimbingState(PlayerHandler* playerHandler);
	void Update(float dt);
	void HandleKeyboard(std::map<int, bool> keyCode);
	State GetName();
};