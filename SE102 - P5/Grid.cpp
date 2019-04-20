#include "Grid.h"

Grid::Grid(Rect MapRect)
{
	columns = floor((float)MapRect.width / (SCREEN_WIDTH >> 1));
	rows = floor((float)MapRect.height / (SCREEN_HEIGHT >> 1));

	for (int y = 0; y <= rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x <= columns; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		cells.push_back(row);
	}
}

std::vector<Cell*> Grid::GetVisibleCells(Rect CameraRect)
{
	std::vector<Cell*> visibleCells;
	int left = CameraRect.x / Cell::width;
	int right = floor((CameraRect.x + CameraRect.width) / Cell::width);
	//int top = CameraRect.y / Cell::height;
	//int bottom = floor(CameraRect.y + CameraRect.height) / Cell::height);

	for (int r = 0; r < 2; ++r)
	{
		for (int c = left; c <= right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}
	return visibleCells;
}

std::vector<Object*> Grid::GetVisibleObjects(std::vector<Cell*> cells)
{
	std::set<Object*> setObjects;

	for (auto c : cells)
	{
		auto objs = c->objects;
		setObjects.insert(objs.begin(), objs.end());
	}
	return std::vector<Object*>(setObjects.begin(), setObjects.end());
}
