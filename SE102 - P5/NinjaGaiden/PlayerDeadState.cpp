#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->GetPlayer()->SetVelocity(0, 0);
}

State PlayerDeadState::GetName()
{
	return DEAD;
}
