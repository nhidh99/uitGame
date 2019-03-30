#include "PlayerFallingState.h"

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_reverse = _playerHandler->Player->isReverse;

	_playerHandler->Player->allow[ATTACKING] = true;
	_playerHandler->Player->allow[CLINGING] = true;
	_playerHandler->Player->vy = PLAYER_FALLING_SPEED;

	StateName = FALLING;
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	if (_playerHandler->Player->vy == 0)
	{
		_playerHandler->Player->ChangeState(new PlayerStandingState(_playerHandler));
		return;
	}

	if (_playerHandler->Player->allow[CLINGING] && _playerHandler->Player->posY < SCREEN_HEIGHT - 20)
	{
		if (_playerHandler->Player->posX == _playerHandler->Player->width >> 1)
		{
			_playerHandler->Player->isReverse = true;
			_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		_playerHandler->Player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
		_playerHandler->Player->isReverse = true;
	}

	else if (keyCode[DIK_RIGHT])
	{
		_playerHandler->Player->vx = _reverse ? PLAYER_RUNNING_SPEED / 2 : PLAYER_RUNNING_SPEED;
		_playerHandler->Player->isReverse = false;
	}

	else
	{
		_playerHandler->Player->vx = 0;
	}
}