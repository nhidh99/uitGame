#include "ObjectItemShuriken.h"

ObjectItemShuriken::ObjectItemShuriken()
{
	_animation = new Animation(ITEM, 2, 2);
	_isOnScreen = false;
	_width = ITEM_SHURIKEN_WIDTH;
	_height = ITEM_SHURIKEN_HEIGHT;
}

void ObjectItemShuriken::SetPosition(float x, float y)
{
	_posX = x + 3;
	_posY = y - 15;
	_vx = _isReverse ? -ITEM_SHURIKEN_SPEED : ITEM_SHURIKEN_SPEED;
}

void ObjectItemShuriken::Update(float dt)
{
	if (_isOnScreen)
	{
		Object::Update(dt);
		if (_posX > SCREEN_WIDTH || _posX < 0)
			_isOnScreen = false;
	}
}

void ObjectItemShuriken::Render()
{
	if (_isOnScreen)
	{
		_animation->FlipHorizontal(_isReverse);
		_animation->Render(_posX, _posY);
	}
}