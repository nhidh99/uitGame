#include "PlayerStandingState.h"

// Khởi tạo State đang đứng của nhân vật
PlayerStandingState::PlayerStandingState()
{
	player->vx = 0;
	player->vy = 0;
	player->allow[MOVING] = true;
	player->allow[JUMPING] = true;
	player->allow[SITTING] = true;
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
		player->ChangeState(new PlayerRunningState());
	}
	// Nhấn phím DOWN -> SITTING
	else if (keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerSittingState());
	}
}