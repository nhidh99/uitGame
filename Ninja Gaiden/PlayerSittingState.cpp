#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState()
{
	player->allow[JUMPING] = false;
	player->vx = 0;
	player->vy = 0;
	player->posY -= 4;
	player->height -= 8;
	StateName = SITTING;
}

void PlayerSittingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí sự kiện bàn phím cho trạng thái ngồi
void PlayerSittingState::HandleKeyboard()
{
	if (!keyCode[DIK_DOWN])
	{
		player->allow[JUMPING] = true;
		player->height += 8;
		player->posY += 4;

		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			player->ChangeState(new PlayerRunningState());
		}
		else
		{
			player->ChangeState(new PlayerStandingState());
		}
	}
}