#include "PlayerAttackingState.h"

// Khởi tạo State ATTACK (tùy vào trạng thái trước đó là đánh hoặc ngồi)
PlayerAttackingState::PlayerAttackingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	_curState = _playerHandler->State->StateName;
	_reverse = _playerHandler->Player->isReverse;
	_playerHandler->Player->allow[JUMPING] = false;
	StateName = (_curState == SITTING) ? ATTACKING_SIT : ATTACKING_STAND;
}

// Update lại tráng thái khi đang ATTACK
void PlayerAttackingState::Update(float dt)
{
	this->HandleKeyboard();

	// Khi đã đánh xong
	if (_playerHandler->Player->curAnimation->isLastFrame)
	{
		_playerHandler->Player->allow[ATTACKING] = true;

		switch (_curState)
		{
		case STANDING: case RUNNING:
			_playerHandler->Player->ChangeState(new PlayerStandingState(_playerHandler));
			return;

		case SITTING:
			_playerHandler->Player->posY -= 5;
			_playerHandler->Player->ChangeState(new PlayerSittingState(_playerHandler));
			return;

		case FALLING:
			_playerHandler->Player->ChangeState(new PlayerFallingState(_playerHandler));
			return;

		case JUMPING:
			_playerHandler->Player->ChangeState(new PlayerJumpingState(_playerHandler));
			return;
		}
	}
	else
	{
		// Khi chưa đánh xong / bắt đầu đánh
		_playerHandler->Player->allow[ATTACKING] = false;

		switch (_curState)
		{
		case RUNNING: case STANDING: case SITTING:
			_playerHandler->Player->vx = 0;
			_playerHandler->Player->vy = 0;
			break;

		case JUMPING:
		{
			// Nếu đã nhảy đến độ cao nhất định -> _curState về trạng thái FALLING
			_playerHandler->Player->vy += GRAVITY_SPEED;

			if ((_playerHandler->Player->vx == SCREEN_WIDTH - _playerHandler->Player->width
				|| _playerHandler->Player->vx == _playerHandler->Player->width >> 1) && _playerHandler->Player->allow[CLINGING])
			{
				_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
				return;
			}

			else if (_playerHandler->Player->vy >= 0)
			{
				_curState = FALLING;
				_playerHandler->Player->vy = PLAYER_FALLING_SPEED;
			}
			break;
		}

		/*case FALLING:
			if ((_playerHandler->Player->posX == SCREEN_WIDTH - _playerHandler->Player->width
				|| _playerHandler->Player->posX == _playerHandler->Player->width >> 1) && _playerHandler->Player->allow[CLINGING])
			{
				_playerHandler->Player->ChangeState(new PlayerClingingState(_playerHandler));
				return;
			}
			break;*/
		}
	}
}

// Xử lí sự kiện bàn phím khi đang ATTACK
void PlayerAttackingState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		_playerHandler->Player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
	}

	else if (keyCode[DIK_RIGHT])
	{
		_playerHandler->Player->vx = !_reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED / 2;
	}
	else _playerHandler->Player->vx = 0;
}