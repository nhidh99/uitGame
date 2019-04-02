#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState()
{
	StateName = CLIMBING;
}

void PlayerClimbingState::Update(float dt)
{
	if (Player::GetInstance()->posY > (SCREEN_HEIGHT >> 1) - 20)
	{
		Player::GetInstance()->posY++;
		Player::GetInstance()->ChangeState(new PlayerFallingState());
		return;
	}

	if (Player::GetInstance()->posY < Player::GetInstance()->height >> 1)
	{
		Player::GetInstance()->posY = Player::GetInstance()->height >> 1;
	}

	this->HandleKeyboard();
}

void PlayerClimbingState::HandleKeyboard()
{
	if (keyCode[DIK_UP])
	{
		Player::GetInstance()->vy = -PLAYER_CLIMBING_SPEED;
	}
	else if (keyCode[DIK_DOWN])
	{
		Player::GetInstance()->vy = PLAYER_CLIMBING_SPEED;
	}
	else
	{
		Player::GetInstance()->ChangeState(new PlayerClingingState());
	}
}