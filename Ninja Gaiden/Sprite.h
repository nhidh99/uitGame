#pragma once
#include "GameGlobal.h"
#include "TextureFactory.h"
#include <vector>

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _texture;
	RECT _rect;
	D3DXVECTOR3 _center;

public:
	Sprite() {};
	Sprite(Tag tag, int left, int top, int right, int bottom);
	virtual void Render(float x, float y, float translateX = 0, float translateY = 0);

	Tag tag;							// Loại Object của Sprite đang xét
	bool isReverse;						// Kiểm tra lật hình theo chiều dọc
};