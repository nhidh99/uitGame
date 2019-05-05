#include "Animation.h"

// Render Animation tại vị trí (x,y) lên màn hình
void Animation::Render(float x, float y, float translateX, float translateY)
{
	_sprites[CurFrameIndex]->isReverse = this->isReverse;
	_sprites[CurFrameIndex]->Render(x, y, translateX, translateY);
}

// Update Animation sau thời gian delta-time
void Animation::Update(float dt)
{
	// Nếu quá thời gian tồn tại của 1 Frame -> chuyển Frame kế
	if (_curFrameTime > _timePerFrame)
	{
		_curFrameTime = 0;
		
		// Kiểm tra đến Frame cuối -> trở lại Frame đầu
		if (++CurFrameIndex == _totalFrames)
		{
			isLastFrame = true;
			CurFrameIndex = 0;
		}
	}
	// Nếu không thì tiếp tục cộng dồn thời gian cho Frame đang xét
	else
	{
		isLastFrame = false;
		_curFrameTime += dt;
	}
}

Animation::Animation(Tag tag, int index)
{
	_sprites.push_back(SpriteFactory::GetInstance()->GetSprite(tag, index));
	_totalFrames = 1;
	_timePerFrame = DEFAULT_TPS;
	CurFrameIndex = 0;
	isLastFrame = false;
}

Animation::Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame)
{
	_sprites = SpriteFactory::GetInstance()->GetSprites(tag, firstIndex, lastIndex);
	_totalFrames = _sprites.size();
	_timePerFrame = timePerFrame;
	CurFrameIndex = 0;
	isLastFrame = false;
}

Sprite * Animation::GetSprite(int i)
{
	return _sprites[i];
}