#pragma once
#include "Sprite.h"

class ObjectItemSprite : public Sprite
{
protected:
	Type _type;			// Loại Item

public:
	ObjectItemSprite(Type type, int left, int top, int right, int bottom);
	Type GetType();
};