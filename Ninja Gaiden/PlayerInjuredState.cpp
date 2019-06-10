#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState()
{
	if (player->isOnWall)
	{
		player->isOnWall = false;

		if (player->isReverse)
		{
			player->posX++;
		}
		else player->posX--;
	}

	player->height = PLAYER_STANDING_HEIGHT;
	player->vy = PLAYER_JUMPING_SPEED;
	player->vx = player->isReverse ? PLAYER_INJURED_SPEED : -PLAYER_INJURED_SPEED;
	StateName = INJURED;
}

void PlayerInjuredState::Update(float dt)
{
	player->vy -= GRAVITY_SPEED;

	if (player->isOnGround)
	{
		Sound::getInstance()->play("jump");
		player->ChangeState(new PlayerStandingState());
	}
}

State PlayerInjuredState::GetName()
{
	return INJURED;
}
