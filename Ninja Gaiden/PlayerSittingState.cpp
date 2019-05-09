#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState()
{
	player->allow[JUMPING] = false;
	player->posY -= 5;
	player->vx = 0;
	player->vy = 0;
	player->height = PLAYER_SITTING_HEIGHT;
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
		player->posY += 5;
		player->height = PLAYER_STANDING_HEIGHT;

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