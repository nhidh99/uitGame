#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState()
{
	StateName = CLIMBING;
}

void PlayerClimbingState::Update(float dt)
{
	this->HandleKeyboard();
}

void PlayerClimbingState::HandleKeyboard()
{
	if (keyCode[DIK_UP]
		&& player->posY + (player->height >> 1) <= player->wallBound.rect.y)
	{
		player->vy = PLAYER_CLIMBING_SPEED;
	}
	else if (keyCode[DIK_DOWN]
		&& player->posY - (player->height >> 1) >= player->wallBound.rect.y - player->wallBound.rect.height)
	{
		player->vy = -PLAYER_CLIMBING_SPEED;
	}
	else
	{
		player->ChangeState(new PlayerClingingState());
	}
}