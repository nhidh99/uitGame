#pragma once
#include "GameGlobal.h"
#include "Object.h"
#include <unordered_set>

class Cell
{
private:
	int xID, yID;

public:
	Rect rect;
	static int width, height;
	std::unordered_set<Object*> objects;
	std::vector<BoundingBox> walls;
	std::vector<BoundingBox> grounds;

	Cell(int xID, int yID);
	bool IsContain(Rect r);
};
