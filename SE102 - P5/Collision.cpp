#include "Collision.h"

Collision*	Collision::instance = NULL;

Collision * Collision::GetInstance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

bool Collision::IsCollision(BoundingBox b1, BoundingBox b2)
{
	return !(b1.x + b1.width < b2.x || b1.x > b2.x + b2.width || b1.y + b1.height < b2.y || b1.y > b2.y + b2.height);
}

CollisionResult Collision::SweptAABB(BoundingBox b1, BoundingBox b2)
{
	CollisionResult result;
	result.isCollide = false;
	result.entryTime = 1;
	result.dir = NONE;

	BoundingBox b;
	b.x = b1.vx > 0 ? b1.x : b1.x + b1.vx;
	b.y = b1.vy > 0 ? b1.y : b1.y + b1.vy;
	b.width = b1.vx > 0 ? b1.vx + b1.width : b1.width - b1.vx;
	b.height = b1.vy > 0 ? b1.vy + b1.height : b1.height - b1.vy;

	if (!IsCollision(b, b2))
		return result;

	if (b1.vx > 0)
	{
		dxEntry = b2.x - (b1.x + b1.width);
		dxExit = (b2.x + b2.width) - b1.x;
	}

	else
	{
		dxEntry = (b2.x + b2.width) - b1.x;
		dxExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0)
	{
		dyEntry = b2.y - (b1.y + b1.height);
		dyExit = (b2.y + b2.height) - b1.y;
	}

	else
	{
 		dyEntry = (b2.y + b2.height) - b1.y;
		dyExit = b2.y - (b1.y + b1.height);
	}

	if (b1.vx == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / b1.vx;
		txExit = dxExit / b1.vx;
	}

	if (b1.vy == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / b1.vy;
		tyExit = dyExit / b1.vy;
	}

	entryTime = max(txEntry, tyEntry);
	exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		return result;
	}
	else
	{
		result.isCollide = true;
		result.entryTime = entryTime;

		if (txEntry > tyEntry)
		{
			if (b1.vx > 0.0f)
			{

				result.dir = LEFT;
				OutputDebugString("LEFT COLLISION\n");
			}
			else
			{
				result.dir = RIGHT;
				OutputDebugString("RIGHT COLLISION\n");
			}
		}
		else
		{
			if (b1.vy > 0.0f)
			{
				result.dir = UP;
				OutputDebugString("UP COLLISION\n");
			}
			else
			{
				result.dir = DOWN;
				OutputDebugString("DOWN COLLISION\n");
			}
		}
		return result;
	}
}