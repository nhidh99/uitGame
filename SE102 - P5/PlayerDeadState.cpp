#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->Player->vx = 0;
	_playerHandler->Player->vy = 0;
}

State PlayerDeadState::GetName()
{
	return DEAD;
}
