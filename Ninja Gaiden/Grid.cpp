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

	// Nếu player attack -> Tạo weapon -> init weapon trong grid
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
	auto it = respawnObjects.begin();
	while (it != respawnObjects.end())
	{
		auto o = *it;
		if (o->tag == ENEMY)
		{
			auto e = (Enemy*)o;
			if (!e->IsRespawnOnScreen())
			{
				e->isDead = false;
				e->ChangeState(STANDING);
				it = respawnObjects.erase(it);
				this->MoveObject(e, e->spawnX, e->spawnY);
				continue;
			}
		}
		++it;
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

	if (BottomCell >= rows)
	{
		this->RemoveObject(obj);
		return;
	}
	else if (TopCell >= rows)
	{
		return;
	}

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

	if (TopCell < rows)
	{
		cells[TopCell][LeftCell]->objects.insert(obj);

		if (LeftCell != RightCell)
		{
			cells[TopCell][RightCell]->objects.insert(obj);
		}
	}

	if (BottomCell < rows)
	{
		if (TopCell != BottomCell)
		{
			cells[BottomCell][LeftCell]->objects.insert(obj);

			if (LeftCell != RightCell)
			{
				cells[BottomCell][RightCell]->objects.insert(obj);
			}
		}
	}
}

void Grid::RestartGame()
{
	isFrozenEnemies = false;
	player->weaponID = 0;

	for (auto o : respawnObjects)
	{
		switch (o->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)o;
			e->isDead = false;
			e->ChangeState(STANDING);
			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->isDead = false;
			break;
		}
		}
		this->MoveObject(o, o->spawnX, o->spawnY);
	}

	for (auto o : this->GetVisibleObjects())
	{
		this->MoveObject(o, o->spawnX, o->spawnY);
	}
	respawnObjects.clear();
}

void Grid::RemoveObject(Object * obj)
{
	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y == rows) break;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->RemoveObject(obj);
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
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(e);
						respawnObjects.push_back(e);
						continue;
					}
					else if (!e->isActive)
					{
						e->ChangeState(ATTACKING);
					}
					break;
				}

				case HOLDER:
				{
					auto h = (Holder*)o;
					if (h->isDead)
					{
						it = c->objects.erase(it);

						auto i = ItemFactory::CreateItem(h->itemID);
						i->posX = h->posX;
						i->posY = h->posY;
						i->DectectGround(this->GetVisibleGrounds());
						this->InitObjectCell(i);
						setObjects.insert(i);

						this->RemoveObject(h);
						this->respawnObjects.push_back(h);
						continue;
					}
					break;
				}

				case ITEM:
				{
					auto i = (Item*)o;
					if (i->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(i);
						delete i;
						continue;
					}
					break;
				}

				case WEAPON:
				{
					auto w = (Weapon*)o;
					if (w->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(w);
						delete w;
						continue;
					}
					break;
				}
				}
				setObjects.insert(o);
			}

			else //Object is out of camera
			{
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isActive)
					{
						e->isActive = false;
						it = c->objects.erase(it);

						if (e->IsRespawnOnScreen())
						{
							this->RemoveObject(e);
							respawnObjects.push_back(e);
						}
						else
						{
							this->MoveObject(e, e->spawnX, e->spawnY);
						}
						continue;
					}
					break;
				}

				case ITEM:
				case WEAPON:
				{
					it = c->objects.erase(it);
					this->RemoveObject(o);
					delete o;
					continue;
					break;
				}
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

std::unordered_set<Object*> Grid::GetColliableObjects(Object * obj)
{
	std::unordered_set<Object*> objs;

	auto r = obj->GetRect();
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y >= rows) break;

		for (int x = LeftCell; x <= RightCell; ++x)
		{
			for (auto o : cells[y][x]->objects)
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

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->grounds.push_back(ground);
		}
	}
}

void Grid::InitWallCell(Rect * wall)
{
	int LeftCell = wall->x / Cell::width;
	int RightCell = (wall->x + wall->width) / Cell::width;
	int TopCell = wall->y / Cell::height;
	int BottomCell = (wall->y - wall->height) / Cell::height;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->walls.push_back(wall);
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

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			cells[y][x]->objects.insert(obj);
		}
	}
}