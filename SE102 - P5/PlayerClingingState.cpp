#include "PlayerClingingState.h"

PlayerClingingState::PlayerClingingState()
{
	player->allow[CLINGING] = false;
	player->allow[ATTACKING] = false;
	player->allow[JUMPING] = true;
	player->sword->isOnScreen = false;

	player->vx = 0;
	player->vy = 0;

	if (player->posX == player->width >> 1)
		player->isReverse = true;
	else player->isReverse = false;

	StateName = CLINGING;
}

void PlayerClingingState::Update(float dt)
{
	this->HandleKeyboard();
}

void PlayerClingingState::HandleKeyboard()
{
	if (keyCode[DIK_UP] || keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerClimbingState());
		return;
	}

	if (keyCode[DIK_SPACE])
	{
		if (!player->isReverse && keyCode[DIK_LEFT])
		{
			player->isReverse = true;
			player->posX--;
			player->ChangeState(new PlayerJumpingState());
		}

		else if (player->isReverse && keyCode[DIK_RIGHT])
		{
			player->isReverse = false;
			player->posX++;
			player->ChangeState(new PlayerJumpingState());
		}
	}
}