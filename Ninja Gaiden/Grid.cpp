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

void Grid::Update()
{
	this->viewPort = camera->GetRect();
	this->UpdateVisibleCells();
	this->RespawnEnemies();
}

void Grid::RespawnEnemies()
{
	auto it = respawnEnemies.begin();
	while (it != respawnEnemies.end())
	{
		auto e = *it;
		if (!e->IsRespawnOnScreen())
		{
			it = respawnEnemies.erase(it);
			this->MoveObject(e, e->spawnX, e->spawnY);
		}
		else ++it;
	}
}

void Grid::MoveObject(Object* obj, float posX, float posY)
{
	auto r = obj->GetRect();
	int oldLeftCell = r.x / Cell::width;
	int oldRightCell = (r.x + r.width) / Cell::width;
	int oldTopCell = r.y / Cell::height;
	int oldBottomCell = (r.y + r.height) / Cell::height;

	obj->posX = posX;
	obj->posY = posY;

	r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y + r.height) / Cell::height;

	if (LeftCell != oldLeftCell)
	{
		cells[oldTopCell][oldLeftCell]->RemoveObject(obj);

		if (oldTopCell != oldBottomCell)
		{
			cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);
		}
	}

	if (RightCell != oldRightCell)
	{
		cells[oldTopCell][oldRightCell]->RemoveObject(obj);

		if (oldTopCell != oldBottomCell)
		{
			cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
		}
	}

	if (TopCell != oldTopCell)
	{
		cells[oldTopCell][oldLeftCell]->RemoveObject(obj);

		if (oldLeftCell != oldRightCell)
		{
			cells[oldTopCell][oldRightCell]->RemoveObject(obj);
		}
	}

	if (BottomCell != oldBottomCell)
	{
		cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);

		if (oldLeftCell != oldRightCell)
		{
			cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
		}
	}

	cells[TopCell][LeftCell]->objects.insert(obj);
	cells[TopCell][RightCell]->objects.insert(obj);

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->objects.insert(obj);
		cells[BottomCell][RightCell]->objects.insert(obj);
	}
}

void Grid::MovePlayer(Player* obj, float posX, float posY)
{
	auto r = obj->GetRect();
	int oldLeftCell = r.x / Cell::width;
	int oldRightCell = (r.x + r.width) / Cell::width;
	int oldTopCell = r.y / Cell::height;
	int oldBottomCell = (r.y + r.height) / Cell::height;

	obj->posX = posX;
	obj->posY = posY;
	r = obj->GetRect();

	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y + r.height) / Cell::height;

	if (oldBottomCell == rows)
	{
		if (TopCell == rows)
		{
			cells[oldTopCell][oldLeftCell]->RemoveObject(obj);
			cells[oldTopCell][oldRightCell]->RemoveObject(obj);

			obj->posX = obj->spawnX;
			obj->posY = obj->spawnY;
			r = obj->GetRect();

			int LeftCell = r.x / Cell::width;
			int RightCell = (r.x + r.width) / Cell::width;
			TopCell = r.y / Cell::height;
			BottomCell = (r.y + r.height) / Cell::height;

			cells[TopCell][LeftCell]->objects.insert(obj);
			cells[TopCell][RightCell]->objects.insert(obj);

			if (TopCell != BottomCell)
			{
				cells[BottomCell][LeftCell]->objects.insert(obj);
				cells[BottomCell][RightCell]->objects.insert(obj);
			}

			for (auto e : respawnEnemies)
			{
				this->MoveObject(e, e->spawnX, e->spawnY);
			}
			respawnEnemies.clear();
		}
	}

	else if (BottomCell != rows)
	{
		MoveObject(obj, posX, posY);
	}
}

void Grid::RemoveObject(Object* obj)
{
	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y + r.height) / Cell::height;

	cells[TopCell][LeftCell]->RemoveObject(obj);
	cells[BottomCell][LeftCell]->RemoveObject(obj);
	cells[TopCell][RightCell]->RemoveObject(obj);
	cells[BottomCell][RightCell]->RemoveObject(obj);
}

void Grid::UpdateVisibleCells()
{
	visibleCells.clear();
	int left = viewPort.x / Cell::width;
	int right = ceil(viewPort.x / Cell::width) + 2;
	//int top = viewPort.y / Cell::height;
	//int bottom = floor(viewPort.y + viewPort.height) / Cell::height);

	for (int r = 0; r < 2; ++r)
	{
		for (int c = left; c < right; ++c)
		{
			visibleCells.push_back(cells[r][c]);
		}
	}
}

std::unordered_set<Object*> Grid::GetVisibleObjects()
{
	std::unordered_set<Object*> setObjects;

	for (auto c : visibleCells)
	{
		auto it = c->objects.begin();
		while (it != c->objects.end())
		{
			auto o = *it;
			if (o->IsCollide(viewPort))
			{
				setObjects.insert(o);
				if (o->tag == ENEMY)
				{
					auto e = (Enemy*)o;
					e->isActive = true;
				}
			}

			else if (o->tag == ENEMY)
			{
				auto e = (Enemy*)o;
				if (e->isActive)
				{
					e->isActive = false;
					it = c->objects.erase(it);

					if (e->IsRespawnOnScreen())
					{
						this->RemoveObject(e);
						respawnEnemies.push_back(e);
					}
					else
					{
						this->MoveObject(e, e->spawnX, e->spawnY);
					}
					continue;
				}
			}
			++it;
		}
	}
	return setObjects;
}

std::set<Rect> Grid::GetVisibleWalls()
{
	std::set<Rect> setWalls;

	for (auto c : visibleCells)
	{
		for (auto w : c->walls)
		{
			if (w.IsContain(viewPort))
			{
				setWalls.insert(w);
			}
		}
	}
	return setWalls;
}

std::set<Rect> Grid::GetVisibleGrounds()
{
	std::set<Rect> setGrounds;

	for (auto c : visibleCells)
	{
		for (auto g : c->grounds)
		{
			if (g.IsContain(viewPort))
			{
				setGrounds.insert(g);
			}
		}
	}
	return setGrounds;
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

void Grid::InitBoundsCell(std::vector<Rect> grounds, std::vector<Rect> walls)
{
	for (auto g : grounds)
	{
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(g))
				{
					cell->grounds.push_back(g);
				}
			}
		}
	}

	for (auto w : walls)
	{
		Rect r = w;
		for (auto row : cells)
		{
			for (auto cell : row)
			{
				if (cell->IsContain(w))
				{
					cell->walls.push_back(w);
				}
			}
		}
	}
}