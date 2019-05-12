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

void Grid::LoadObjects()
{
	Loader* loader = new Loader();
	auto grounds = loader->LoadGroundsBound();
	auto walls = loader->LoadWallsBound();
	auto holders = loader->LoadHolders();
	auto enemies = loader->LoadEnemies();
	for (auto g : grounds)	this->InitGroundCell(g);
	for (auto w : walls)	this->InitWallCell(w);
	for (auto h : holders)	this->InitObjectCell(h);
	for (auto e : enemies)	this->InitObjectCell(e);
}

void Grid::RespawnEnemies()
{
	auto it = respawnEnemies.begin();
	while (it != respawnEnemies.end())
	{
		auto e = *it;
		if (!e->IsRespawnOnScreen())
		{
			e->ChangeState(STANDING);
			it = respawnEnemies.erase(it);
			this->MoveObject(e, e->spawnX, e->spawnY);
		}
		else ++it;
	}
}

void Grid::MoveObject(Object * obj, float posX, float posY)
{
	auto r = obj->GetRect();
	int oldLeftCell = r.x / Cell::width;
	int oldRightCell = (r.x + r.width) / Cell::width;
	int oldTopCell = r.y / Cell::height;
	int oldBottomCell = (r.y - r.height) / Cell::height;

	obj->posX = posX;
	obj->posY = posY;

	r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

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

	if (LeftCell != RightCell)
	{
		cells[TopCell][RightCell]->objects.insert(obj);
	}

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->objects.insert(obj);

		if (LeftCell != RightCell)
		{
			cells[BottomCell][RightCell]->objects.insert(obj);
		}
	}
}

void Grid::RestartGame()
{
	for (auto e : respawnEnemies)
	{
		e->ChangeState(STANDING);
		this->MoveObject(e, e->spawnX, e->spawnY);
	}

	for (auto o : this->GetVisibleObjects())
	{
		this->MoveObject(o, o->spawnX, o->spawnY);
	}

	respawnEnemies.clear();
}


void Grid::RemoveObject(Object * obj)
{
	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	cells[TopCell][LeftCell]->RemoveObject(obj);

	if (LeftCell != RightCell)
	{
		cells[TopCell][RightCell]->RemoveObject(obj);
	}

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->RemoveObject(obj);

		if (LeftCell != RightCell)
		{
			cells[BottomCell][RightCell]->RemoveObject(obj);
		}
	}
}

void Grid::UpdateVisibleCells()
{
	visibleCells.clear();
	int left = viewPort.x / Cell::width;
	int right = ceil(viewPort.x / Cell::width) + 2;
	//int bottom = viewPort.y / Cell::height;
	//int top = floor(viewPort.y + viewPort.height) / Cell::height);

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
				if (o->tag == ENEMY)
				{
					auto e = (Enemy*)o;
					if (e->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(e);
						respawnEnemies.push_back(e);
						continue;
					}
					else
					{
						e->ChangeState(ATTACKING);
					}
				}
				setObjects.insert(o);
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

std::unordered_set<Rect*> Grid::GetVisibleWalls()
{
	std::unordered_set<Rect*> setWalls;

	for (auto c : visibleCells)
	{
		for (auto w : c->walls)
		{
			if (w->IsContain(viewPort))
			{
				setWalls.insert(w);
			}
		}
	}
	return setWalls;
}

std::unordered_set<Rect*> Grid::GetVisibleGrounds()
{
	std::unordered_set<Rect*> setGrounds;

	for (auto c : visibleCells)
	{
		for (auto g : c->grounds)
		{
			if (g->IsContain(viewPort))
			{
				setGrounds.insert(g);
			}
		}
	}
	return setGrounds;
}

std::unordered_set<Object*> Grid::GetColliableObjects()
{
	std::unordered_set<Object*> objs;

	auto r = player->rect;
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	if (TopCell < rows)
	{
		for (auto o : cells[TopCell][LeftCell]->objects)
		{
			objs.insert(o);
		}

		if (LeftCell != RightCell)
		{
			for (auto o : cells[TopCell][RightCell]->objects)
			{
				objs.insert(o);
			}
		}
	}

	if (TopCell != BottomCell)
	{
		for (auto o : cells[BottomCell][RightCell]->objects)
		{
			objs.insert(o);
		}

		if (LeftCell != RightCell)
		{
			for (auto o : cells[BottomCell][RightCell]->objects)
			{
				objs.insert(o);
			}
		}
	}
	return objs;
}

void Grid::InitGroundCell(Rect * ground)
{
	int LeftCell = ground->x / Cell::width;
	int RightCell = (ground->x + ground->width) / Cell::width;
	int TopCell = ground->y / Cell::height;
	int BottomCell = (ground->y - ground->height) / Cell::height;

	cells[TopCell][LeftCell]->grounds.push_back(ground);

	if (LeftCell != RightCell)
	{
		cells[TopCell][RightCell]->grounds.push_back(ground);
	}

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->grounds.push_back(ground);

		if (LeftCell != RightCell)
		{
			cells[BottomCell][RightCell]->grounds.push_back(ground);
		}
	}
}

void Grid::InitWallCell(Rect * wall)
{
	int LeftCell = wall->x / Cell::width;
	int RightCell = (wall->x + wall->width) / Cell::width;
	int TopCell = wall->y / Cell::height;
	int BottomCell = (wall->y - wall->height) / Cell::height;

	cells[TopCell][LeftCell]->walls.push_back(wall);

	if (LeftCell != RightCell)
	{
		cells[TopCell][RightCell]->walls.push_back(wall);
	}

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->walls.push_back(wall);

		if (LeftCell != RightCell)
		{
			cells[BottomCell][RightCell]->walls.push_back(wall);
		}
	}
}

void Grid::InitObjectCell(Object * obj)
{
	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	cells[TopCell][LeftCell]->objects.insert(obj);

	if (LeftCell != RightCell)
	{
		cells[TopCell][RightCell]->objects.insert(obj);
	}

	if (TopCell != BottomCell)
	{
		cells[BottomCell][LeftCell]->objects.insert(obj);

		if (LeftCell != RightCell)
		{
			cells[BottomCell][RightCell]->objects.insert(obj);
		}
	}
}