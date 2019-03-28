#pragma once
#include "Sprite.h"
#include "SpriteFactory.h"
#include <vector>
#include <map>

class Animation
{
private:
	int _totalFrames;						// Tổng số Frame
	int _timePerFrame;						// Thời gian tồn tại mỗi frame trước khi chuyển
	int _curFrameTime;						// Thời gian hiện tại của Frame đang xét
	std::vector<Sprite*> _sprites;			// Các Sprite (Frame) để tạo nên Animation

public:
	Animation() {};
	Animation(Tag tag, int index);
	Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame = DEFAULT_TPS);									
	void Render(float x, float y, float translateX = 0, float translateY = 0);
	void Update(float dt);

	int CurFrameIndex;
	bool isLastFrame;
	bool isReverse;
	Sprite* GetSprite(int index);
};