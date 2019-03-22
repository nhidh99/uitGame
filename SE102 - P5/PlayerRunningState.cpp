#include "PlayerRunningState.h"

// Khởi tạo RUNNING với tốc độ chạy cho trước
PlayerRunningState::PlayerRunningState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_runningSpeed = PLAYER_RUNNING_SPEED;
	_playerHandler->Player->allow[ATTACKING] = true;
	_playerHandler->Player->allow[JUMPING] = true;
	_playerHandler->Player->vy = 0;
	StateName = RUNNING;
}

void PlayerRunningState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí sự kiện bàn phím theo nút DIRECTION (LEFT/RIGHT), quy định chiều chạy
void PlayerRunningState::HandleKeyboard()
{
	if (keyCode[DIK_RIGHT])
	{
		_playerHandler->Player->isReverse = false;
		_playerHandler->Player->vx = _runningSpeed;
	}

	else if (keyCode[DIK_LEFT])
	{
		_playerHandler->Player->isReverse = true;
		_playerHandler->Player->vx = -_runningSpeed;
	}

	else
	{
		_playerHandler->Player->ChangeState(new PlayerStandingState(_playerHandler));
	}
}