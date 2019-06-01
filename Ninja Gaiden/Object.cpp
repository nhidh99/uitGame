#include "Object.h"

Rect Object::GetRect()
{
	Rect rect;
	rect.x = posX - (width >> 1);
	rect.y = posY + (height >> 1);
	rect.width = this->width;
	rect.height = this->height;
	return rect;
}

BoundingBox Object::GetBoundingBox()
{
	BoundingBox bound;
	bound.left = posX - (width >> 1);
	bound.top = posY + (height >> 1);
	bound.right = bound.left + width;
	bound.bottom = bound.top - height;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Object::Update(float dt)
{
	dx = vx * dt;
	dy = vy * dt;
	posX += dx;
	posY += dy;
}

bool Object::IsCollide(Rect r)
{
	return this->GetRect().IsContain(r);
}
