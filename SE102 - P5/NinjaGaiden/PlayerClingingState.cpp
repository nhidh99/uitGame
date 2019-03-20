#include "PlayerClingingState.h"
#define _player _playerHandler->GetPlayer()

PlayerClingingState::PlayerClingingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_player->Allow(CLINGING, false);
	_player->Allow(ATTACKING, false);
	_player->Allow(JUMPING, true);
	_player->GetSword()->OnScreen(false);
	_player->GetSwingSword()->OnScreen(false);
	_player->SetVelocity(0, 0);

	if (_player->GetPosX() == _player->GetWidth() >> 1)
		_player->Reverse(true);
	else _player->Reverse(false);
}

void PlayerClingingState::Update(float dt)
{

}

void PlayerClingingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (keyCode[DIK_UP] || keyCode[DIK_DOWN])
	{
		_player->ChangeState(new PlayerClimbingState(_playerHandler));
		return;
	}

	if (keyCode[DIK_SPACE])
	{
		if (!_player->IsReverse() && keyCode[DIK_LEFT])
		{
			_player->Reverse(true);
			_player->SetPosX(_player->GetPosX() - 1);
			_player->ChangeState(new PlayerJumpingState(_playerHandler));
		}

		else if (_player->IsReverse() && keyCode[DIK_RIGHT])
		{
			_player->Reverse(false);
			_player->SetPosX(_player->GetPosX() + 1);
			_player->ChangeState(new PlayerJumpingState(_playerHandler));
		}
	}
}

State PlayerClingingState::GetName()
{
	return CLINGING;
}