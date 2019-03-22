#pragma once
#include "PlayerHandler.h"
#include "Object.h"
#include <map>

class PlayerState
{
protected:
	PlayerHandler* _playerHandler;			// Handler chuyển đổi qua lại các thuộc tính và state của player

public:
	PlayerState() {};
	PlayerState(PlayerHandler* playerHandler) { _playerHandler = playerHandler; }
	virtual ~PlayerState() { if (_playerHandler) delete _playerHandler; }	
	virtual void Update(float dt) = 0;
	virtual void HandleKeyboard() = 0;		// Xử lí các sự kiện nhấn phím

	State StateName;
};