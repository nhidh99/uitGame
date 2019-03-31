#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerSittingState.h"
#include "PlayerRunningState.h"
#include "PlayerAttackingState.h"
#include "PlayerJumpingState.h"
#include "PlayerClingingState.h"
#include "PlayerClimbingState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState();
	~PlayerStandingState() {}
	void Update(float dt);
	void HandleKeyboard();
};