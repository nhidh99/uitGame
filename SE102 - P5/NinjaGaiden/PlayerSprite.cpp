#include "PlayerSprite.h"

// Khởi tạo Sprite Player như Sprite với khung RECT cần cắt
PlayerSprite::PlayerSprite(State state, int left, int top, int right, int bottom)
{
	_tag = PLAYER;
	_state = state;
	_isFlipHorizontal = false;

	_rect.top = top;
	_rect.left = left;
	_rect.right = right;
	_rect.bottom = bottom;

	// Định kích thước của Player (vì không hẳn kích thước RECT cắt = kích thước PLAYER)
	_width = PLAYER_WIDTH;
	switch (_state)
	{
	case STANDING: case RUNNING:
	case ATTACKING_STAND:
	case CLIMBING:
	case CLINGING:
	case THROWING:
		_height = PLAYER_STANDING_HEIGHT;
		break;

	case JUMPING: case FALLING: case SITTING:
	case ATTACKING_SIT:
		_height = PLAYER_SITTING_HEIGHT;
		break;
	}
}

void PlayerSprite::Render(float x, float y, float translateX, float translateY)
{
	Sprite::Render(x, y, translateX, translateY);
}

State PlayerSprite::GetState()
{
	return _state;
}
