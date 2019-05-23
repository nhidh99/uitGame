#include "Grid.h"

void Grid::CreateGridFile(int level)
{
	std::ifstream ifile;
	char gridFileName[30];
	sprintf_s(gridFileName, "Resources\\grid%d.txt", level);

	// Nếu không tìm thấy file grid -> Tạo file từ map objects trong level đó
	ifile.open(gridFileName);
	if (ifile.fail())
	{
		ifile.close();

		// Đọc file matrix để lấy size map -> xác định số cell trong grid
		char fileMapName[30];
		sprintf_s(fileMapName, "Resources\\matrix%d.txt", level);
		ifile.open(fileMapName);

		int numTiles, rowTiles, colTiles;
		ifile >> numTiles >> colTiles >> rowTiles;
		ifile.close();

		int colCell = ceil((float)(colTiles * TILE_SIZE) / (SCREEN_WIDTH >> 1));
		int rowCell = ceil((float)(rowTiles * TILE_SIZE) / (SCREEN_HEIGHT >> 1));

		// Đọc từng loại object và đẩy vào grid (mỗi loại có thông số cách tính Rect khác nhau)
		char objectsFileName[30];
		sprintf_s(objectsFileName, "Resources\\objects%d.txt", level);
		ifile.open(objectsFileName);

		auto objs = std::vector<GameObject*>();

		while (!ifile.eof())
		{
			auto obj = new GameObject();
			Rect* rect = NULL;
			char type;
			int value;

			ifile >> type;
			obj->type = type;

			switch (type)
			{
			case 'g': //ground: x, y, width, height
			case 'w': //wall: x, y, width, height, climbable
			{
				int n = (type == 'g' ? 4 : 5);
				for (int i = 0; i < n; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				rect = new Rect(obj->value[0], obj->value[1], obj->value[2], obj->value[3]);
				break;
			}

			case 'h': //holder: holderID, posX, posY, itemID
			{
				for (int i = 0; i < 4; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				auto h = HolderFactory::CreateHolder(obj->value[0], obj->value[3]);
				h->posX = obj->value[1];
				h->posY = obj->value[2];
				rect = new Rect(h->GetRect());
				delete h;
				break;
			}

			case 'e': //enemy: enemyID, posX, posY
			{
				for (int i = 0; i < 3; ++i)
				{
					ifile >> value;
					obj->value.push_back(value);
				}

				auto e = EnemyFactory::CreateEnemy(obj->value[0]);
				e->posX = obj->value[1];
				e->posY = obj->value[2];
				rect = new Rect(e->GetRect());
				delete e;
				break;
			}
			}

			// Xác định cell object đó và đẩy vào
			obj->leftCell = rect->x / Cell::width;
			obj->rightCell = (rect->x + rect->width) / Cell::width;
			obj->topCell = rect->y / Cell::height;
			obj->bottomCell = (rect->y - rect->height) / Cell::height;
			delete rect;

			objs.push_back(obj);
		}

		// Viết ra file grid
		std::ofstream ofile;
		ofile.open(gridFileName);
		ofile << colCell << " " << rowCell << " " << objs.size();

		for (auto o : objs)
		{
			ofile << "\n" << o->type;
			for (auto v : o->value)
			{
				ofile << " " << v;
			}
			ofile << "\n" << o->leftCell << " " << o->topCell << " " << o->rightCell << " " << o->bottomCell;
		}

		//Sau khi có các thông số, xoá GridObject
		ifile.close();
		ofile.close();
	}
	else ifile.close();
}

Grid::Grid(int level)
{
	this->CreateGridFile(level);

	std::ifstream ifile;
	char gridFileName[30];
	sprintf_s(gridFileName, "Resources\\grid%d.txt", level);

	int numObjects;
	ifile.open(gridFileName);
	ifile >> columns >> rows >> numObjects;

	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < columns; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		cells.push_back(row);
	}

	int value;
	char type;
	int top, left, right, bottom;
	std::vector<int> values;

	for (int i = 0; i < numObjects; ++i)
	{
		ifile >> type;
		switch (type)
		{
		case 'g': // ground: x,y,width,height
		{
			for (int i = 0; i < 4; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto ground = new Rect(values[0], values[1], values[2], values[3]);

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				for (int c = left; c <= right; ++c)
				{
					cells[r][c]->grounds.push_back(ground);
				}
			}
			break;
		}

		case 'w': // wall: x,y,width,height,climable
		{
			for (int i = 0; i < 5; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto wall = new Wall(values[0], values[1], values[2], values[3], values[4]);

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				for (int c = left; c <= right; ++c)
				{
					cells[r][c]->walls.push_back(wall);
				}
			}
			break;
		}
		
		case 'h': // holder: typeID, posX, posY, itemID
		{
			for (int i = 0; i < 4; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto holder = HolderFactory::CreateHolder(values[0], values[3]);
			holder->spawnX = holder->posX = values[1];
			holder->spawnY = holder->posY = values[2];

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				for (int c = left; c <= right; ++c)
				{
					cells[r][c]->objects.insert(holder);
				}
			}
			break;
		}

		case 'e': // enemy: typeID, posX, posY
		{
			for (int i = 0; i < 3; ++i)
			{
				ifile >> value;
				values.push_back(value);
			}
			auto enemy = EnemyFactory::CreateEnemy(values[0]);
			enemy->spawnX = enemy->posX = values[1];
			enemy->spawnY = enemy->posY = values[2];

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				for (int c = left; c <= right; ++c)
				{
					cells[r][c]->objects.insert(enemy);
				}
			}
			break;
		}
		}
		values.clear();
	}
	ifile.close();
}

void Grid::Update()
{
	this->viewPort = camera->GetRect();
	this->UpdateVisibleCells();
	this->RespawnEnemies();
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

	if (TopCell >= rows || BottomCell < 0 || LeftCell <= 0 || RightCell > columns)
	{
		return;
	}

	else if (BottomCell >= rows || TopCell < 0 || RightCell <= 0 || LeftCell > columns)
	{
		this->RemoveObject(obj);
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
	player->weaponType = NONE;

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
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
			else cells[y][x]->RemoveObject(obj);
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

std::unordered_set<Wall*> Grid::GetVisibleWalls()
{
	std::unordered_set<Wall*> setWalls;

	for (auto c : visibleCells)
	{
		for (auto w : c->walls)
		{
			if (w->rect.IsContain(viewPort))
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
		if (y < 0 || y >= rows) continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= columns) continue;
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

void Grid::InitWallCell(Wall * wall)
{
	auto r = wall->rect;
	int LeftCell = r.x / Cell::width;
	int RightCell = (r.x + r.width) / Cell::width;
	int TopCell = r.y / Cell::height;
	int BottomCell = (r.y - r.height) / Cell::height;

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