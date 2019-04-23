#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include <set>
#include "Cell.h"
#include "Enemy.h"

class Grid
{
private:
	int rows;
	int columns;

public:
	Grid(Rect MapRect);
	std::vector<std::vector<Cell*>> cells;
	std::vector<Cell*> visibleCells;

	void Update(Rect CameraRect);
	std::vector<Object*> GetVisibleObjects(Rect CameraRect);
	std::vector<BoundingBox> GetVisibleWalls(Rect CameraRect);
	std::vector<BoundingBox> GetVisibleGrounds(Rect CameraRect);

	void InitEnemiesCell(std::vector<Enemy*> enemies);
	void InitBoundsCell(std::vector<BoundingBox> grounds, std::vector<BoundingBox> walls);
};