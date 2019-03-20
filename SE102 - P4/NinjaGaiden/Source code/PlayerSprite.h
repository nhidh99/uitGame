#pragma once
#include "Sprite.h"

// Sprite cho Player, dùng thiết đặt lại một số kích thước và vị trí Translate khi Render
// Cho một số Sprite đặc biệt (khi cắt bằng RECT)
class PlayerSprite : public Sprite
{
private:
	State _state;
public:
	PlayerSprite(State state, int left, int top, int right, int bottom);
	void Render(float x, float y, float translateX = 0, float translateY = 0);
	State GetState();
};