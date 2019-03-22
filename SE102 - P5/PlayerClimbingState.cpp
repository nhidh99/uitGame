#include "PlayerClimbingState.h"


PlayerClimbingState::PlayerClimbingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_climbingSpeed = PLAYER_CLIMBING_SPEED;
	StateName = CLIMBING;
}

void PlayerClimbingState::Update(float dt)
{
	if (_playerHandler->Player->posY > (SCREEN_HEIGHT >> 1) - 20)
	{
		_playerHandler->Player->posY++;
		_playerHandler->Player->ChangeState(new PlayerFallingState(_playerHandler));
		return;
	}

	if (_playerHandler->Player->posY < _playerHandler->Player->height >> 1)
	{
		_playerHandler->Player->posY = _playerHandler->Player->height >> 1;
	}

	this->HandleKeyboard();
}

void PlayerClimbingState::HandleKeyboard()
{
	if (keyCode[DIK_UP])
	{
		_playerHandler->Player->vy = -_climbingSpeed;
	}
	else if (keyCode[DIK_DOWN])
	{
		_playerHandler->Player->vy = _climbingSpeed;
	}
	else
	{
		_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
	}
}