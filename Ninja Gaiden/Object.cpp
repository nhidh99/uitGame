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
	bound.height = height;
	bound.width = width;
	bound.x = posX - (width >> 1);
	bound.y = posY + (height >> 1);
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
