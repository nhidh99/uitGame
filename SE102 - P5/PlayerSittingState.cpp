#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->Player->allow[JUMPING] = false;
	_playerHandler->Player->posY += 5;
	_playerHandler->Player->vx = 0;
	_playerHandler->Player->vy = 0;
	_playerHandler->Player->height = PLAYER_SITTING_HEIGHT;
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
		_playerHandler->Player->posY -= 5;
		_playerHandler->Player->height = PLAYER_STANDING_HEIGHT;

		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			_playerHandler->Player->ChangeState(new PlayerRunningState(_playerHandler));
		}
		else
		{
			_playerHandler->Player->ChangeState(new PlayerStandingState(_playerHandler));
		}
	}
}