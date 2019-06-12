#include "PlayerFallingState.h"

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState()
{
	_reverse = player->isReverse;
	player->allow[ATTACKING] = true;
	player->allow[CLINGING] = true;
	player->vy = -PLAYER_FALLING_SPEED;
	StateName = FALLING;
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	if (player->vy == 0)
	{
		Sound::getInstance()->play("jump");
		player->ChangeState(new PlayerStandingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
		player->isReverse = true;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->vx = _reverse ? PLAYER_RUNNING_SPEED / 2 : PLAYER_RUNNING_SPEED;
		player->isReverse = false;
	}

	else
	{
		player->vx = 0;
	}
}