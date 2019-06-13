#pragma once
#include "GameGlobal.h"
#include "TextureFactory.h"
#include <vector>

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	D3DXVECTOR3 center;

public:
	Sprite() {};
	Sprite(Tag tag, int left, int top, int right, int bottom);
	virtual void Render(float x, float y, float translateX = 0, float translateY = 0);
	virtual void ScaleRender(float x, float y, float scaleX, float scaleY, float translateX = 0, float translateY = 0);

	Tag tag;							// Loại Object của Sprite đang xét
	bool isReverse;						// Kiểm tra lật hình theo chiều 
	float posX;
	float posY;
};