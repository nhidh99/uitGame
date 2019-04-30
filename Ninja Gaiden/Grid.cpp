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

void Grid::Update(Rect CameraRect)
{
	visibleCells.clear();
	int left = CameraRect.x / Cell::width;
	int right = floor(CameraRect.x / Cell::width) + 2;
	//int top = CameraRect.y / Cell::height;
	//int bottom = floor(CameraRect.y + CameraRect.height) / Cell::height);

	for (int r = 0; r < 2; ++r)
	{
		for (int c = left; c <= right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}

	auto it = respawnEnemies.begin();
	while (it != respawnEnemies.end())
	{
		auto e = *it;
		auto isRespawnOnScreen = Rect(e->spawnX - (e->width >> 1), e->spawnY - (e->height >> 1), e->width, e->height).IsContain(CameraRect);

		if (isRespawnOnScreen)
		{
			e->posX = -100;
			e->posY = -100;
			++it;
		}
		else
		{
			e->posX = e->spawnX;
			e->posY = e->spawnY;
			it = respawnEnemies.erase(it);
		}
	}
}

std::vector<Object*> Grid::GetVisibleObjects(Rect CameraRect)
{
	std::unordered_set<Object*> setObjs;

	for (auto c : visibleCells)
	{
		for (auto o : c->objects)
		{
			if (o->IsCollide(CameraRect))
			{
				setObjs.insert(o);
			}
			else if (o->tag == ENEMY)
			{
				auto e = (Enemy*)o;
				auto isRespawnOnScreen = Rect(e->spawnX - (e->width >> 1), e->spawnY - (e->height >> 1), e->width, e->height).IsContain(CameraRect);

				if (isRespawnOnScreen)
				{
					respawnEnemies.push_back(e);
				}
				else
				{
					e->posX = e->spawnX;
					e->posY = e->spawnY;
				}
			}
		}
	}
	return std::vector<Object*>(setObjs.begin(),setObjs.end());
}

std::vector<BoundingBox> Grid::GetVisibleWalls(Rect CameraRect)
{
	std::set<BoundingBox> setWalls;

	for (auto c : visibleCells)
	{
		for (auto w : c->walls)
		{
			if (w.IsContain(CameraRect))
			{
				setWalls.insert(w);
			}
		}
	}
	return std::vector<BoundingBox>(setWalls.begin(), setWalls.end());
}

std::vector<BoundingBox> Grid::GetVisibleGrounds(Rect CameraRect)
{
	std::set<BoundingBox> setGrounds;

	for (auto c : visibleCells)
	{
		for (auto g : c->grounds)
		{
			if (g.IsContain(CameraRect))
			{
				setGrounds.insert(g);
			}
		}
	}
	return std::vector<BoundingBox>(setGrounds.begin(), setGrounds.end());
}

void Grid::InitHoldersCell(std::vector<Holder*> holders)
{
	for (auto h : holders)
	{
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(h->GetRect()))
				{
					cell->objects.push_back(h);
				}
			}
		}
	}
}

void Grid::InitEnemiesCell(std::vector<Enemy*> enemies)
{
	for (auto e : enemies)
	{
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(e->GetRect()))
				{
					cell->objects.push_back(e);
				}
			}
		}
	}
}

void Grid::InitBoundsCell(std::vector<BoundingBox> grounds, std::vector<BoundingBox> walls)
{
	for (auto g : grounds)
	{
		Rect r = Rect(g.x, g.y, g.width, g.height);
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(r))
				{
					cell->grounds.push_back(g);
				}
			}
		}
	}

	for (auto w : walls)
	{
		Rect r = Rect(w.x, w.y, w.width, w.height);
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(r))
				{
					cell->walls.push_back(w);
				}
			}
		}
	}
}