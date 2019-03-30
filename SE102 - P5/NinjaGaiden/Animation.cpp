#include "Animation.h"

// Render Animation tại vị trí (x,y) lên màn hình
void Animation::Render(float x, float y)
{
	_sprites[_curFrame]->Render(x, y);
}

// Update Animation sau thời gian delta-time
void Animation::Update(float dt)
{
	// Nếu quá thời gian tồn tại của 1 Frame -> chuyển Frame kế
	if (_curFrameTime > _timePerFrame)
	{
		_curFrameTime = 0;
		_curFrame++;

		// Kiểm tra đến Frame cuối -> trở lại Frame đầu
		if (_curFrame == _totalFrames)
		{
			_isLastFrame = true;
			_curFrame = 0;
		}
	}
	// Nếu không thì tiếp tục cộng dồn thời gian cho Frame đang xét
	else
	{
		_isLastFrame = false;
		_curFrameTime += dt;
	}
}

void Animation::SetCurIndex(int index)
{
	_curFrame = index;
}

Animation::Animation(Tag tag, int index)
{
	_tag = tag;
	_sprites.push_back(SpriteFactory::GetInstance()->GetSprite(tag, index));
	_curFrame = 0;
	_totalFrames = 1;
	_timePerFrame = TIME_PER_FRAME;
	_isLastFrame = false;
}

Animation::Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame)
{
	_tag = tag;
	_sprites = SpriteFactory::GetInstance()->GetSprites(tag, firstIndex, lastIndex);
	_curFrame = 0;
	_totalFrames = _sprites.size();
	_timePerFrame = timePerFrame;
	_isLastFrame = false;
}

// Lật Animation (các Frames) theo chiều dọc
void Animation::FlipHorizontal(bool flag)
{
	_sprites[_curFrame]->FlipHorizontal(flag);
}

// === Các hàm Get ====

int Animation::GetWidth()
{
	return _sprites[0]->GetWidth();
}

int Animation::GetHeight()
{
	return _sprites[0]->GetHeight();
}

int Animation::GetCurIndex()
{
	return _curFrame;
}

RECT Animation::GetRect()
{
	return _sprites[_curFrame]->GetRect();
}

bool Animation::IsLastFrame()
{
	return _isLastFrame;
}

Sprite * Animation::GetSprite(int i)
{
	return _sprites[i];
}
