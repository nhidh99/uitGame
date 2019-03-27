#include "PlayerJumpingState.h"

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerJumpingState::PlayerJumpingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_reverse = _playerHandler->Player->isReverse;
	_jumpingSpeed = PLAYER_JUMPING_SPEED;

	_playerHandler->Player->allow[ATTACKING] = true;
	_playerHandler->Player->allow[CLINGING] = true;

	State prevState = playerHandler->State->StateName;

	if (prevState == RUNNING || prevState == STANDING || prevState == CLINGING)
		_playerHandler->Player->vy = -GRAVITY_SPEED;

	StateName = JUMPING;
}

void PlayerJumpingState::Update(float dt)
{
	// Cập nhật tốc độ vy đến khi vy >= 0 -> FALLING
	_playerHandler->Player->vy += _jumpingSpeed;

	if (_playerHandler->Player->vy >= 0)
	{
		_playerHandler->Player->ChangeState(new PlayerFallingState(_playerHandler));
		return;
	}

	if (_playerHandler->Player->allow[CLINGING] && _playerHandler->Player->posY < (SCREEN_HEIGHT >> 1) - 20)
	{
		//if (_playerHandler->Player->posX == SCREEN_WIDTH - _playerHandler->Player->width)
		//{
		//	_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
		//	return;
		//}

		if (_playerHandler->Player->posX == _playerHandler->Player->width >> 1)
		{
			_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}
	}

	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard()
{
	_playerHandler->Player->vx = 0;

	if (keyCode[DIK_LEFT])
	{
		_playerHandler->Player->isReverse = true;
		_playerHandler->Player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
	}

	else if (keyCode[DIK_RIGHT])
	{
		_playerHandler->Player->isReverse = false;
		_playerHandler->Player->vx = _reverse ? PLAYER_RUNNING_SPEED / 2 : PLAYER_RUNNING_SPEED;
	}
}