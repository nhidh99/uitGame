#include "PlayerRunningState.h"

// Khởi tạo RUNNING với tốc độ chạy cho trước
PlayerRunningState::PlayerRunningState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_runningSpeed = PLAYER_RUNNING_SPEED;
	_playerHandler->GetPlayer()->Allow(ATTACKING, true);
	_playerHandler->GetPlayer()->Allow(JUMPING, true);
	_playerHandler->GetPlayer()->SetVy(0);
}

// Xử lí sự kiện bàn phím theo nút DIRECTION (LEFT/RIGHT), quy định chiều chạy
void PlayerRunningState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (keyCode[VK_RIGHT])
	{
		_playerHandler->GetPlayer()->Reverse(false);
		_playerHandler->GetPlayer()->SetVelocity(_runningSpeed, 0);
	}

	else if (keyCode[VK_LEFT])
	{
		_playerHandler->GetPlayer()->Reverse(true);
		_playerHandler->GetPlayer()->SetVelocity(-_runningSpeed, 0);
	}

	else
	{
		_playerHandler->GetPlayer()->ChangeState(new PlayerStandingState(_playerHandler));
	}
}

State PlayerRunningState::GetName()
{
	return RUNNING;
}
