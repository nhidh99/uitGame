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
	virtual void Update(float dt);
	void HandleKeyboard(std::map<int, bool> keyCode);
	State GetName();
};