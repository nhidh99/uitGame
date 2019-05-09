#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState()
{
	StateName = CLIMBING;
}

void PlayerClimbingState::Update(float dt)
{
	if (player->posY > (SCREEN_HEIGHT >> 1) - 20)
	{
		player->posY++;
		player->ChangeState(new PlayerFallingState());
		return;
	}

	if (player->posY < player->height >> 1)
	{
		player->posY = player->height >> 1;
	}

	this->HandleKeyboard();
}

void PlayerClimbingState::HandleKeyboard()
{
	if (keyCode[DIK_UP])
	{
		player->vy = -PLAYER_CLIMBING_SPEED;
	}
	else if (keyCode[DIK_DOWN])
	{
		player->vy = PLAYER_CLIMBING_SPEED;
	}
	else
	{
		player->ChangeState(new PlayerClingingState());
	}
}