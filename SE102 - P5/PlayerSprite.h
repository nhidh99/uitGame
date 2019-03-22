#pragma once
#include "Sprite.h"

// Sprite cho Player, dùng thiết đặt lại một số kích thước và vị trí Translate khi Render
// Cho một số Sprite đặc biệt (khi cắt bằng RECT)
class PlayerSprite : public Sprite
{
public:
	PlayerSprite(State state, int left, int top, int right, int bottom)
	{
		tag = PLAYER;
		_texture = TextureFactory::GetInstance()->GetTexture(PLAYER);
		_rect.top = top;
		_rect.left = left;
		_rect.right = right;
		_rect.bottom = bottom;
		_center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};