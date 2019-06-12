#include "Collision.h"

Collision* Collision::instance = NULL;

Collision* Collision::GetInstance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

bool Collision::IsCollision(BoundingBox b1, BoundingBox b2)
{
	return !(b1.left > b2.right || b1.right < b2.left || b1.top < b2.bottom || b1.bottom > b2.top);
}

CollisionResult Collision::SweptAABB(BoundingBox b1, BoundingBox b2)
{
	CollisionResult result;
	result.isCollide = false;
	result.entryTime = 1.0f;
	result.nx = result.ny = 0;

	b1.vx = b1.vx - b2.vx;
	b1.vy = b1.vy - b2.vy;

	BoundingBox broadphasebox;
	broadphasebox.top = b1.vy > 0 ? b1.top + b1.vy : b1.top;
	broadphasebox.bottom = b1.vy > 0 ? b1.bottom : b1.bottom + b1.vy;
	broadphasebox.left = b1.vx > 0 ? b1.left : b1.left + b1.vx;
	broadphasebox.right = b1.vx > 0 ? b1.right + b1.vx : b1.right;

	if (!IsCollision(broadphasebox, b2))
	{
		return result;
	}

	if (b1.vx > 0)
	{
		dxEntry = b2.left - b1.right;
		dxExit = b2.right - b1.left;
	}
	else
	{
		dxEntry = b2.right - b1.left;
		dxExit = b2.left - b1.right;
	}

	if (b1.vy > 0.0f)
	{
		dyEntry = b2.bottom - b1.top;
		dyExit = b2.top - b1.bottom;
	}
	else
	{
		dyEntry = b2.top - b1.bottom;
		dyExit = b2.bottom - b1.top;
	}

	if (b1.vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / b1.vx;
		txExit = dxExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / b1.vy;
		tyExit = dyExit / b1.vy;
	}

	// Tim thoi gian lon nhat va nho nhat khi va cham 
	entryTime = max(txEntry, tyEntry);
	exitTime = min(txExit, tyExit);

	// Neu khong co va cham
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
			result.nx = (dxEntry < 0 ? 1 : -1);
		}
		else
		{
			result.ny = (dyEntry < 0 ? 1 : -1);
		}
		return result;
	}
}