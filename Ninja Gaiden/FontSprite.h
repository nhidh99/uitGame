#pragma once
#include "Sprite.h"

class FontSprite : public Sprite 
{
public:
	Type type;
	char c;
	FontSprite();
	FontSprite(char _c, int left, int top, int right, int bottom);

	void Render(char _c, float x, float y);
};