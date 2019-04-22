#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include <set>
#include "Object.h"

class Cell
{
	int xID, yID;

public:
	Rect rect;
	static int width, height;
	std::vector<Object*> objects;

	Cell(int xID, int yID);
	bool IsContain(Rect r);
};

class Grid
{
private:
	int rows;
	int columns;

public:
	std::vector<std::vector<Cell*>> cells;
	Grid(Rect MapRect);
	std::vector<Object*> GetVisibleObjects(Rect CameraRect);
};