#pragma once
#include "Player.h"
#include <map>


class PlayerState
{
public:
	PlayerState() {}
	virtual void Update(float dt) = 0;
	virtual void HandleKeyboard() = 0;		// Xử lí các sự kiện nhấn phím
	State StateName;
};