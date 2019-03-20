#include "PlayerAttackingState.h"
#define _player _playerHandler->GetPlayer()

// Khởi tạo State ATTACK (tùy vào trạng thái trước đó là đánh hoặc ngồi)
PlayerAttackingState::PlayerAttackingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_curState = _playerHandler->GetState()->GetName();
	_reverse = _player->IsReverse();
	_player->Allow(JUMPING, false);

	if (_curState == SITTING)
	{
		_attackState = ATTACKING_SIT;
	}
	else _attackState = ATTACKING_STAND;
}

PlayerAttackingState::~PlayerAttackingState()
{
}

// Update lại tráng thái khi đang ATTACK
void PlayerAttackingState::Update(float dt)
{
	// Khi đã đánh xong
	if (_player->IsLastFrame() && !_player->IsAllow(ATTACKING))
	{
		_player->Allow(ATTACKING, true);

		switch (_curState)
		{
		case STANDING: case RUNNING:
			_player->ChangeState(new PlayerStandingState(_playerHandler));
			break;

		case SITTING:
			_player->AddPosY(-5);
			_player->ChangeState(new PlayerSittingState(_playerHandler));
			break;

		case FALLING:
			_player->ChangeState(new PlayerFallingState(_playerHandler));
			break;

		case JUMPING:
			_player->ChangeState(new PlayerJumpingState(_playerHandler));
			break;
		}
	}
	else
	{
		// Khi chưa đánh xong / bắt đầu đánh
		_player->Allow(ATTACKING, false);

		switch (_curState)
		{
		case RUNNING: case STANDING: case SITTING:
			_player->SetVelocity(0, 0);
			break;

		case JUMPING:
		{
			// Nếu đã nhảy đến độ cao nhất định -> _curState về trạng thái FALLING
			auto vy = _player->GetVy();
			_player->SetVy(vy + PLAYER_JUMPING_SPEED);

			if (_player->GetVy() >= 0)
			{
				_curState = FALLING;
				_player->SetVy(GRAVITY_SPEED);
			}

			if ((_player->GetPosX() == SCREEN_WIDTH - _player->GetWidth()
				|| _player->GetPosX() == _player->GetWidth() >> 1) && _player->IsAllow(CLINGING))
			{
				_player->ChangeState(new PlayerClingingState(_playerHandler));
				return;
			}
			break;
		}

		case FALLING:
			// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
			if (_player->GetPosY() >= SCREEN_HEIGHT >> 1)
			{
				if (!_player->GetSword()->IsOnScreen())
				{
					_player->ChangeState(new PlayerStandingState(_playerHandler));
					return;
				}
				else
				{
					_curState = STANDING;
					_player->SetPosY(SCREEN_HEIGHT >> 1);
					_player->SetVelocity(0, 0);
				}
			}

			if ((_player->GetPosX() == SCREEN_WIDTH - _player->GetWidth()
				|| _player->GetPosX() == _player->GetWidth() >> 1) && _player->IsAllow(CLINGING))
			{
				_player->ChangeState(new PlayerClingingState(_playerHandler));
				return;
			}
			break;
		}
	}
}

// Xử lí sự kiện bàn phím khi đang ATTACK
void PlayerAttackingState::HandleKeyboard(std::map<int, bool> keyCode)
{
	if (!keyCode[VK_DOWN] && _curState == SITTING)
		_curState = STANDING;

	if (keyCode[VK_LEFT])
	{
		_player->SetVx(_reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2);
	}

	else if (keyCode[VK_RIGHT])
	{
		_player->SetVx(!_reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED / 2);
	}
	else _player->SetVx(0);
}

State PlayerAttackingState::GetName()
{
	return _attackState;
}