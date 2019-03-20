#include "ObjectItem.h"

bool ObjectItem::IsOnScreen()
{
	return _isOnScreen;
}

void ObjectItem::OnScreen(bool flag)
{
	_isOnScreen = flag;
}

void ObjectItem::Render()
{
	if (_isOnScreen)
	{
		_animation->Render(_posX, _posY);
	}
}
