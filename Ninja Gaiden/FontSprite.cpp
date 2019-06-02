#include "FontSprite.h"

FontSprite::FontSprite()
{
}

FontSprite::FontSprite(char c, int left, int top, int right, int bottom)
{
	this->c = c;
	this->tag = FONT;

	this->_texture = TextureFactory::GetInstance()->GetTexture(this->tag);
	this->_rect.left = left;
	this->_rect.top = top;
	this->_rect.right = right;
	this->_rect.bottom = bottom;
	_center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
}

void FontSprite::Render(char _c, float x, float y)
{
	if (this->c == _c)
	{
		Sprite::Render(x, y, 0, 0);
	}
}
