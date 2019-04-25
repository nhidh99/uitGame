#include "PlayerRunningState.h"

// Khởi tạo RUNNING với tốc độ chạy cho trước
PlayerRunningState::PlayerRunningState()
{
	player->allow[ATTACKING] = true;
	player->allow[JUMPING] = true;
	player->vy = 0;
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
		player->isReverse = false;
		player->vx = PLAYER_RUNNING_SPEED;
	}

	else if (keyCode[DIK_LEFT])
	{
		player->isReverse = true;
		player->vx = -PLAYER_RUNNING_SPEED;
	}

	else
	{
		player->ChangeState(new PlayerStandingState());
	}
}