#include "PlayerFallingState.h"

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_fallingSpeed = GRAVITY_SPEED;
	_reverse = _playerHandler->Player->isReverse;

	_playerHandler->Player->allow[ATTACKING] = true;
	_playerHandler->Player->allow[CLINGING] = true;

	if (_playerHandler->State->StateName == JUMPING
		|| _playerHandler->State->StateName == CLIMBING)
		_playerHandler->Player->vy = _fallingSpeed;

	StateName = FALLING;
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	// Collision bằng set tọa độ cứng (xem như với mặt đất và cạnh màn hình)
	if (_playerHandler->Player->posY > SCREEN_HEIGHT >> 1)
	{
		_playerHandler->Player->posY = SCREEN_HEIGHT >> 1;
		_playerHandler->Player->ChangeState(new PlayerStandingState(_playerHandler));
		return;
	}

	if (_playerHandler->Player->allow[CLINGING] && _playerHandler->Player->posY < SCREEN_HEIGHT - 20)
	{
		//if (_playerHandler->Player->posX == SCREEN_WIDTH - _playerHandler->Player->width)
		//{
		//	_playerHandler->Player->isReverse = false;
		//	_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
		//	return;
		//}

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