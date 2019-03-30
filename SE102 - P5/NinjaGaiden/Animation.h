#pragma once
#include "Sprite.h"
#include "SpriteFactory.h"
#include <vector>
#include <map>

class Animation
{
private:
	Tag _tag;								// Loại Object của Animation
	int _curFrame;							// Frame hiện tại
	int _totalFrames;						// Tổng số Frame
	int _timePerFrame;						// Thời gian tồn tại mỗi frame trước khi chuyển
	int _curFrameTime;						// Thời gian hiện tại của Frame đang xét
	int _curWidthFrame;						// Chiều dài Frame
	int _curHeightFrame;					// Chiều rộng Frame
	bool _isLastFrame;						// Kiểm tra đã tới Frame cuối chưa
	std::vector<Sprite*> _sprites;			// Các Sprite (Frame) để tạo nên Animation

public:
	Animation() {};
	Animation(Tag tag, int index);
	Animation(Tag tag, int firstIndex, int lastIndex, int timePerFrame = TIME_PER_FRAME);
	void FlipHorizontal(bool flag);											
	void Render(float x, float y);											
	void Update(float dt);													
	void SetCurIndex(int index);

	// Các hàm Get một số thuộc tính
	int GetWidth();
	int GetHeight();
	int GetCurIndex();
	RECT GetRect();
	bool IsLastFrame();
	Sprite* GetSprite(int i);
};