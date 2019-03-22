#include "PlayerStandingState.h"

// Khởi tạo State đang đứng của nhân vật
PlayerStandingState::PlayerStandingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->Player->vx = 0;
	_playerHandler->Player->vy = 0;
	_playerHandler->Player->swingSword->isOnScreen = false;
	_playerHandler->Player->allow[JUMPING] = true;
	_playerHandler->Player->allow[ATTACKING] = true;
	StateName = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí các sự kiện bàn phím cho nhân vật
void PlayerStandingState::HandleKeyboard()
{
	// Nhấn phím di chuyển -> RUNNING
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		_playerHandler->Player->ChangeState(new PlayerRunningState(_playerHandler));
	}
	// Nhấn phím DOWN -> SITTING
	else if (keyCode[DIK_DOWN])
	{
		_playerHandler->Player->ChangeState(new PlayerSittingState(_playerHandler));
	}
}