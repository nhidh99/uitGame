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
	result.entryTime = 1.0f;
	result.nx = result.ny = 0;

	float vx = b1.vx - b2.vx;
	float vy = b1.vy - b2.vy;

	BoundingBox b;
	b.x = vx > 0 ? b1.x : b1.x + vx;
	b.y = vy > 0 ? b1.y : b1.y + vy;
	b.width = vx > 0 ? vx + b1.width : b1.width - vx;
	b.height = vy > 0 ? vy + b1.height : b1.height - vy;

	if (!IsCollision(b, b2))
		return result;

	if (vx > 0.0f)
	{
		dxEntry = b2.x - (b1.x + b1.width);
		dxExit = (b2.x + b2.width) - b1.x;
	}

	else
	{
		dxEntry = (b2.x + b2.width) - b1.x;
		dxExit = b2.x - (b1.x + b1.width);
	}

	if (vy > 0.0f)
	{
		dyEntry = b2.y - (b1.y + b1.height);
		dyExit = (b2.y + b2.height) - b1.y;
	}

	else
	{
		dyEntry = (b2.y + b2.height) - b1.y;
		dyExit = b2.y - (b1.y + b1.height);
	}

	if (vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / vx;
		txExit = dxExit / vx;
	}

	if (vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;
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
			result.nx = (vx > 0.0f ? -1 : 1);
		}
		else
		{
			result.ny = (vy > 0.0f ? 1 : -1);
		}
		return result;
	}
}