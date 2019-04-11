#pragma once
#include "GameGlobal.h"
#include "Object.h"
#include "Collision.h"

class Cell
{
	int xID, yID;
	int width, height;
	std::vector<Object*> objects;

	bool IsContain(Rect r)
	{
		return !(rect.x + rect.width < r.x || rect.x > r.x + r.width || rect.y + rect.height < r.y || rect.y > r.y + r.height);
	}

public:
	Rect rect;
	Cell(int xID, int yID)
	{
		this->xID = xID;
		this->yID = yID;
		rect.x = xID * (SCREEN_WIDTH >> 1);
		rect.y = yID * (SCREEN_HEIGHT >> 1);
		rect.width = SCREEN_WIDTH >> 1;
		rect.height = SCREEN_HEIGHT >> 1;
	}

	void ListObjectsInCell(std::vector<Object*> objects)
	{
		objects.clear();
		for (auto obj : objects)
		{
			if (this->IsContain(obj->GetRect()))
			{
				objects.push_back(obj);
			}
		}
	}
};

class Grid
{
private:
	int rows;
	int columns;
	std::vector<Object*> objectsInCamera;

public:
	std::vector<std::vector<Cell*>> grid;

	Grid(Rect MapRect)
	{
		int row = floor((float)MapRect.width / (SCREEN_WIDTH >> 1));
		int columns = floor((float)MapRect.height / (SCREEN_HEIGHT >> 1));

		for (int i = 0; i < row; ++i)
		{
			auto cells = std::vector<Cell*>();
			for (int j = 0; j < columns; ++j)
			{
				cells.push_back(new Cell(i, j));
			}
			grid.push_back(cells);
		}
	}

	void ListObjectsInCamera(Rect CameraRect)
	{
		
	}
};