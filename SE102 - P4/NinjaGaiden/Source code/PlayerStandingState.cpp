#include "PlayerStandingState.h"

// Khởi tạo State đang đứng của nhân vật
PlayerStandingState::PlayerStandingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->GetPlayer()->SetVelocity(0, 0);
	_playerHandler->GetPlayer()->GetSwingSword()->OnScreen(false);
	_playerHandler->GetPlayer()->Allow(JUMPING, true);
	_playerHandler->GetPlayer()->Allow(ATTACKING, true);
}

// Xử lí các sự kiện bàn phím cho nhân vật
void PlayerStandingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	// Nhấn phím di chuyển -> RUNNING
	if (keyCode[VK_LEFT] || keyCode[VK_RIGHT])
	{
		_playerHandler->GetPlayer()->ChangeState(new PlayerRunningState(_playerHandler));
	}
	// Nhấn phím DOWN -> SITTING
	else if (keyCode[VK_DOWN])
	{
		_playerHandler->GetPlayer()->ChangeState(new PlayerSittingState(_playerHandler));
	}
}

State PlayerStandingState::GetName()
{
	return STANDING;
}