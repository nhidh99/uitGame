#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_playerHandler->GetPlayer()->AddPosY(5);
	_playerHandler->GetPlayer()->SetVelocity(0, 0);
}

void PlayerSittingState::Update(float dt)
{
	
}

// Xử lí sự kiện bàn phím cho trạng thái ngồi
void PlayerSittingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (!keyCode[VK_DOWN])
	{
		_playerHandler->GetPlayer()->SetPosY(_playerHandler->GetPlayer()->GetPosY() - 5);
		_playerHandler->GetPlayer()->ChangeState(new PlayerStandingState(_playerHandler));
	}
}

State PlayerSittingState::GetName()
{
	return SITTING;
}
