#include "PlayerDeadState.h"

PlayerDeadState::PlayerDeadState()
{
	player->vx = 0;
	player->vy = 0;
}

State PlayerDeadState::GetName()
{
	return DEAD;
}
