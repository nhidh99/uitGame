#include "PlayerClimbingState.h"
#define _player _playerHandler->GetPlayer()

PlayerClimbingState::PlayerClimbingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_climbingSpeed = PLAYER_CLIMBING_SPEED;
}

void PlayerClimbingState::Update(float dt)
{
	if (_player->GetPosY() < _player->GetHeight() >> 1)
	{
		_player->SetPosY(_player->GetHeight() >> 1);
	}

	if (_player->GetPosY() > (SCREEN_HEIGHT >> 1) - 20)
	{
		_player->SetPosY(_player->GetPosY() + 1);
		_player->ChangeState(new PlayerFallingState(_playerHandler));
	}
}

void PlayerClimbingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (keyCode[VK_UP])
	{
		_player->SetVy(-_climbingSpeed);
	}
	else if (keyCode[VK_DOWN])
	{
		_player->SetVy(_climbingSpeed);
	}
	else
	{
		_player->ChangeState(new PlayerClingingState(_playerHandler));
	}
}

State PlayerClimbingState::GetName()
{
	return CLIMBING;
}
