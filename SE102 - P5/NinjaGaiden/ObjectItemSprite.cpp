#include "ObjectItemSprite.h"

ObjectItemSprite::ObjectItemSprite(Type type, int left, int top, int right, int bottom)
{
	_tag = ITEM;
	_type = type;

	_rect.top = top;
	_rect.left = left;
	_rect.right = right;
	_rect.bottom = bottom;

	_width = _rect.right - _rect.left;
	_height = _rect.top - _rect.bottom;
}

Type ObjectItemSprite::GetType() 
{
	return _type;
}
