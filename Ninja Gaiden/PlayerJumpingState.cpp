#include "PlayerJumpingState.h"

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerJumpingState::PlayerJumpingState()
{
	_reverse = player->isReverse;
	player->allow[ATTACKING] = true;
	player->allow[CLINGING] = true;

	State prevState = player->state->StateName;

	if (prevState == RUNNING || prevState == STANDING || prevState == CLINGING)
		player->vy = PLAYER_JUMPING_SPEED;

	StateName = JUMPING;
}

void PlayerJumpingState::Update(float dt)
{
	// Cập nhật tốc độ vy đến khi vy >= 0 -> FALLING
	player->vy -= GRAVITY_SPEED;

	if (player->vy <= 0)
	{
		player->ChangeState(new PlayerFallingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard()
{
	player->vx = 0;

	if (keyCode[DIK_LEFT])
	{
		player->isReverse = true;
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->isReverse = false;
		player->vx = _reverse ? PLAYER_RUNNING_SPEED / 2 : PLAYER_RUNNING_SPEED;
	}
}