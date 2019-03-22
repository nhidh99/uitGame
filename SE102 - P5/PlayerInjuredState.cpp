#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_isReverse = _playerHandler->Player->isReverse;

	/*
	TODO: Update Vận tốc (như JUMPING -> FALLING -> STANDING nhưng ngược hướng)
	Thực hiện khi xét Collision
	*/
}

void PlayerInjuredState::Update(float dt)
{
	/*
	TODO: Update Vận tốc (như JUMPING -> FALLING -> STANDING nhưng ngược hướng)
	Thực hiện khi xét Collision
	*/
}

State PlayerInjuredState::GetName()
{
	return INJURED;
}
