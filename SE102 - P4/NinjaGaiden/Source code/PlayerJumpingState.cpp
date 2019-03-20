#include "PlayerJumpingState.h"
#define _player _playerHandler->GetPlayer()

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerJumpingState::PlayerJumpingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_reverse = _player->IsReverse();
	_jumpingSpeed = PLAYER_JUMPING_SPEED;

	_player->Allow(ATTACKING, true);
	_player->Allow(CLINGING, true);

	if (playerHandler->GetState()->GetName() == RUNNING || playerHandler->GetState()->GetName() == STANDING
		|| playerHandler->GetState()->GetName() == CLINGING)
		_player->SetVelocity(0, -GRAVITY_SPEED);
}

void PlayerJumpingState::Update(float dt)
{
	// Cập nhật tốc độ vy đến khi vy >= 0 -> FALLING
	auto vy = _player->GetVy();
	_player->SetVy(vy + _jumpingSpeed);

	if (_player->GetVy() >= 0)
	{
		_player->ChangeState(new PlayerFallingState(_playerHandler));
		return;
	}

	if (_player->IsAllow(CLINGING) && _player->GetPosY() < (SCREEN_HEIGHT >> 1) - 20)
	{
		if (_player->GetPosX() == SCREEN_WIDTH - _player->GetWidth())
		{
			_player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}

		if (_player->GetPosX() == _player->GetWidth() >> 1)
		{
			_player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}
	}
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	_player->SetVx(0);

	if (keyCode[VK_LEFT])
	{
		_player->Reverse(true);
		_player->SetVx(_reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2);
	}

	else if (keyCode[VK_RIGHT])
	{
		_player->Reverse(false);
		_player->SetVx(!_reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED / 2);
	}
}

State PlayerJumpingState::GetName()
{
	return JUMPING;
}
