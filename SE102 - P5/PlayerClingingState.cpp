#include "PlayerClingingState.h"

PlayerClingingState::PlayerClingingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->Player->allow[CLINGING] = false;
	_playerHandler->Player->allow[ATTACKING] = false;
	_playerHandler->Player->allow[JUMPING] = true;

	_playerHandler->Player->sword->isOnScreen = false;

	_playerHandler->Player->vx = 0;
	_playerHandler->Player->vy = 0;

	if (_playerHandler->Player->posX == _playerHandler->Player->width >> 1)
		_playerHandler->Player->isReverse = true;
	else _playerHandler->Player->isReverse = false;

	StateName = CLINGING;
}

void PlayerClingingState::Update(float dt)
{
	this->HandleKeyboard();
}

void PlayerClingingState::HandleKeyboard()
{
	if (keyCode[DIK_UP] || keyCode[DIK_DOWN])
	{
		_playerHandler->Player->ChangeState(new PlayerClimbingState(_playerHandler));
		return;
	}

	if (keyCode[DIK_SPACE])
	{
		if (!_playerHandler->Player->isReverse && keyCode[DIK_LEFT])
		{
			_playerHandler->Player->isReverse = true;
			_playerHandler->Player->posX--;
			_playerHandler->Player->ChangeState(new PlayerJumpingState(_playerHandler));
		}

		else if (_playerHandler->Player->isReverse && keyCode[DIK_RIGHT])
		{
			_playerHandler->Player->isReverse = false;
			_playerHandler->Player->posX++;
			_playerHandler->Player->ChangeState(new PlayerJumpingState(_playerHandler));
		}
	}
}