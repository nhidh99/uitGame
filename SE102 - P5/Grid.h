#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include <set>
#include "Object.h"

class Grid
{
private:
	int rows;
	int columns;

public:
	std::vector<std::vector<Cell*>> cells;
	Grid(Rect MapRect);
	std::vector<Cell*> GetVisibleCells(Rect CameraRect);
	std::vector<Object*> GetVisibleObjects(std::vector<Cell*> cells);
};