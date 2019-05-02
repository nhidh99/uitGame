#include "Grid.h"

Grid::Grid(Rect MapRect)
{
	columns = ceil((float)MapRect.width / (SCREEN_WIDTH >> 1));
	rows = ceil((float)MapRect.height / (SCREEN_HEIGHT >> 1));

	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < columns; ++x)
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
	int right = ceil(CameraRect.x / Cell::width) + 2;
	//int top = CameraRect.y / Cell::height;
	//int bottom = floor(CameraRect.y + CameraRect.height) / Cell::height);

	for (int r = 0; r < 2; ++r)
	{
		for (int c = left; c < right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}

	auto it = respawnEnemies.begin();
	while (it != respawnEnemies.end())
	{
		auto e = *it;
		if (!e->IsRespawnOnScreen(CameraRect))
		{
			e->posX = e->spawnX;
			e->posY = e->spawnY;
			it = respawnEnemies.erase(it);
		}
		else ++it;
	}
}

void Grid::UpdateObjects(Object* obj, float dx, float dy)
{
	auto r = obj->GetRect();
	int oldLeftCell = r.x / Cell::width;
	int oldRightCell = (r.x + r.width) / Cell::width;
	int oldTopCell = r.y / Cell::height;
	int oldBottomCell = (r.y + r.height) / Cell::height;

	r.x += dx;
	r.y += dy;

	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y + r.height) / Cell::height;

	if (obj->vx > 0)
	{
		if (LeftCell != oldLeftCell)
		{
			auto objs = &cells[oldTopCell][oldLeftCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}

			objs = &cells[oldBottomCell][oldLeftCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}
		}

		if (RightCell != oldRightCell)
		{
			auto objs = &cells[TopCell][RightCell]->objects;
			(*objs).insert(obj);

			objs = &cells[BottomCell][RightCell]->objects;
			(*objs).insert(obj);
		}
	}

	else if (obj->vx < 0)
	{
		if (RightCell != oldRightCell)
		{
			auto objs = &cells[oldTopCell][oldRightCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}

			objs = &cells[oldBottomCell][oldRightCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}
		}

		if (LeftCell != oldLeftCell)
		{
			auto objs = &cells[TopCell][LeftCell]->objects;
			(*objs).insert(obj);

			objs = &cells[BottomCell][LeftCell]->objects;
			(*objs).insert(obj);
		}
	}

	if (obj->vy > 0)
	{
		if (TopCell != oldTopCell)
		{
			auto objs = &cells[oldTopCell][oldLeftCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}

			objs = &cells[oldTopCell][oldRightCell]->objects;

			if ((*objs).find(obj) != (*objs).end())
			{
				(*objs).erase(obj);
			}
		}

		if (BottomCell != oldBottomCell)
		{
			auto objs = &cells[BottomCell][RightCell]->objects;
			(*objs).insert(obj);

			objs = &cells[BottomCell][LeftCell]->objects;
			(*objs).insert(obj);
		}

		else if (obj->vy < 0)
		{
			if (BottomCell != oldBottomCell)
			{
				auto objs = &cells[oldBottomCell][oldLeftCell]->objects;
				if ((*objs).find(obj) != (*objs).end())
				{
					(*objs).erase(obj);
				}

				objs = &cells[oldBottomCell][oldRightCell]->objects;
				if ((*objs).find(obj) != (*objs).end())
				{
					(*objs).erase(obj);
				}
			}

			if (TopCell != oldTopCell)
			{
				auto objs = &cells[TopCell][RightCell]->objects;
				(*objs).insert(obj);

				objs = &cells[TopCell][LeftCell]->objects;
				(*objs).insert(obj);
			}
		}
	}
}

std::unordered_set<Object*> Grid::GetVisibleObjects(Rect CameraRect)
{
	std::unordered_set<Object*> setObjects;

	for (auto c : visibleCells)
	{
		auto it = c->objects.begin();
		for (auto o : c->objects)
		{
			if (o->IsCollide(CameraRect))
			{
				setObjects.insert(o);
			}
			else if (o->tag == ENEMY)
			{
				auto e = (Enemy*)o;

				if (e->IsRespawnOnScreen(CameraRect))
				{
					e->posY = -100;
					//c->objects.erase(o);
					//cells[(int)(e->posY - (e->height >> 1)) / Cell::height][(int)(e->posX - (e->width >> 1)) / Cell::width]->objects.erase(e);
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
	return setObjects;
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
					cell->objects.insert(h);
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
					cell->objects.insert(e);
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