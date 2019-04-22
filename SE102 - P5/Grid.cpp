#include "Grid.h"

int Cell::width = SCREEN_WIDTH >> 1;
int Cell::height = SCREEN_HEIGHT >> 1;

Cell::Cell(int xID, int yID)
{
	this->xID = xID;
	this->yID = yID;
	rect.x = xID * (SCREEN_WIDTH >> 1);
	rect.y = yID * (SCREEN_HEIGHT >> 1);
	width = rect.width = SCREEN_WIDTH >> 1;
	height = rect.height = SCREEN_HEIGHT >> 1;
}

bool Cell::IsContain(Rect r)
{
	return !(rect.x + rect.width < r.x || rect.x > r.x + r.width || rect.y + rect.height < r.y || rect.y > r.y + r.height);
}

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

std::vector<Object*> Grid::GetVisibleObjects(Rect CameraRect)
{
	std::vector<Cell*> visibleCells;
	int left = CameraRect.x / Cell::width;
	int right = left + (int)(SCREEN_WIDTH / Cell::width) + 1;
	//int top = CameraRect.y / Cell::height;
	//int bottom = floor(CameraRect.y + CameraRect.height) / Cell::height);

	for (int r = 0; r < 2; ++r)
	{
		for (int c = left; c < right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}

	std::set<Object*> setObjects;

	for (auto c : visibleCells)
	{
		for (auto o : c->objects)
			if (o->IsCollide(CameraRect))
				setObjects.insert(o);
	}
	return std::vector<Object*>(setObjects.begin(), setObjects.end());
}
