#pragma once
#include "GameGlobal.h"
#include "TextureFactory.h"
#include <vector>

class Sprite
{
protected:
	Tag _tag;							// Loại Object của Sprite đang xét
	RECT _rect;							// Khung hình chữ nhật bao quanh Sprite
	int _width, _height;				// Kích thước (chỉ xét theo Object của Sprite)
	bool _isFlipHorizontal;				// Kiểm tra lật hình theo chiều dọc
	
public:
	Sprite() {};
	Sprite(Tag tag, int left, int top, int right, int bottom);
	
	void SetWidth(int width);
	void SetHeight(int height);
	void FlipHorizontal(bool flag);
	virtual void Render(float x, float y, float translateX = 0, float translateY = 0);

	int GetWidth();
	int GetHeight();
	RECT GetRect();
	Tag GetTag();
};