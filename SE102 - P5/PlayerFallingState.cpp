﻿#include "PlayerFallingState.h"

Player* player;

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState(PlayerHandler * playerHandler)
{
	_playerHandler = playerHandler;
	player = _playerHandler->Player;
	_reverse = player->isReverse;

	player->allow[ATTACKING] = true;
	player->allow[CLINGING] = true;
	player->vy = PLAYER_FALLING_SPEED;

	StateName = FALLING;
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	if (player->allow[CLINGING] && player->posY < SCREEN_HEIGHT - 20)
	{
		if (player->posX == player->width >> 1)
		{
			player->isReverse = true;
			player->ChangeState(new PlayerClingingState(_playerHandler));
			return;
		}
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