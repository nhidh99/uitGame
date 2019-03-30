#include "PlayerFallingState.h"
#define _player _playerHandler->GetPlayer()

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_fallingSpeed = GRAVITY_SPEED;
	_reverse = _player->IsReverse();

	_player->Allow(ATTACKING, true);
	_player->Allow(CLINGING, true);

	if (_playerHandler->GetState()->GetName() == JUMPING
		|| _playerHandler->GetState()->GetName() == CLIMBING)
		_player->SetVy(_fallingSpeed);
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	// Collision bằng set tọa độ cứng (xem như với mặt đất và cạnh màn hình)
	if (_player->GetPosY() > SCREEN_HEIGHT >> 1)
	{
		_player->SetPosY(SCREEN_HEIGHT >> 1);
		_player->ChangeState(new PlayerStandingState(_playerHandler));
		return;
	}

	if (_player->IsAllow(CLINGING) && _player->GetPosY() < SCREEN_HEIGHT - 20)
	{
		if (_player->GetPosX() == SCREEN_WIDTH - _player->GetWidth())
		{
			_player->Reverse(false);
			_player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}

		if (_player->GetPosX() == _player->GetWidth() >> 1)
		{
			_player->Reverse(true);
			_player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (keyCode[DIK_LEFT])
	{
		_player->SetVx(_reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2);
		_player->Reverse(true);
	}

	else if (keyCode[DIK_RIGHT])
	{
		_player->SetVx(!_reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED / 2);
		_player->Reverse(false);
	}

	else
	{
		_player->SetVx(0);
	}
}

State PlayerFallingState::GetName()
{
	return FALLING;
}