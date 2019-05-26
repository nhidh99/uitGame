#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState()
{
	player->allow[THROWING] = player->allow[JUMPING] = player->allow[ATTACKING] = false;
	player->vy = PLAYER_JUMPING_SPEED;
	player->vx = player->isReverse ? PLAYER_INJURED_SPEED : -PLAYER_INJURED_SPEED;
	StateName = INJURED;
}

void PlayerInjuredState::Update(float dt)
{
	player->vy -= GRAVITY_SPEED;

	if (player->isOnGround)
	{
		player->ChangeState(new PlayerStandingState());
	}
}

State PlayerInjuredState::GetName()
{
	return INJURED;
}
