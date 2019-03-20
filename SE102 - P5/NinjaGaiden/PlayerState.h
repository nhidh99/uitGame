#pragma once
#include "PlayerHandler.h"
#include "Object.h"
#include <map>

/*
Các State sử dụng cho Player
  - Standing: đứng yên
  - Running: chạy, có gia tốc
  - Jumping, Falling: nhảy và rơi có gia tốc
  - Attacking: Đánh roi
  - Throwing: Ném item
Các trạng thái di chuyển có gia tốc chỉ đạt đến một mức độ tối đa
*/

class PlayerState
{
protected:
	PlayerHandler* _playerHandler;			// Handler chuyển đổi qua lại các thuộc tính và state của player

public:
	PlayerState() {};
	virtual ~PlayerState() { if (_playerHandler) delete _playerHandler; }
	PlayerState(PlayerHandler* playerHandler) { _playerHandler = playerHandler; }

	virtual void Update(float dt) = 0;
	virtual void HandleKeyboard(std::map<int, bool> keyCode) = 0;		// Xử lí các sự kiện nhấn phím
	virtual State GetName() = 0;										// Lấy tên của State để thuận tiện xét các trường hợp
};