#pragma once
#include "Object.h"

class ObjectGround : public Object
{
public:
	BoundingBox bound;

	ObjectGround(float x, float y, float w, float h)
	{
		bound.height = h;
		bound.width = w;
		bound.x = x;
		bound.y = y;
		bound.vx = bound.vy = 0;
	}
};