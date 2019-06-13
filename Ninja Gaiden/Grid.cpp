#include "Grid.h"

void Grid::CreateGridFile(int level)
{
	std::ifstream ifile;
	char gridFileName[30];
	sprintf_s(gridFileName, "Resources\\Texts\\grid%d.txt", level);

	// Nếu không tìm thấy file grid -> Tạo file từ map objects trong level đó
	ifile.open(gridFileName);
	if (ifile.fail())
	{
		ifile.close();

		// Đọc file matrix để lấy size map -> xác định số cell trong grid
		char fileMapName[30];
		sprintf_s(fileMapName, "Resources\\Texts\\matrix%d.txt", level);
		ifile.open(fileMapName);

		int numTiles, rowTiles, colTiles;
		ifile >> numTiles >> colTiles >> rowTiles;
		ifile.close();

		int colCell = ceil((float)(colTiles * TILE_SIZE) / (SCREEN_WIDTH >> 1));
		int rowCell = ceil((float)(rowTiles * TILE_SIZE) / (SCREEN_HEIGHT >> 1)) + 1;

		// Đọc từng loại object và đẩy vào grid (mỗi loại có thông số cách tính Rect khác nhau)
		char objectsFileName[30];
		sprintf_s(objectsFileName, "Resources\\Texts\\objects%d.txt", level);
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

				// PANTHER, EAGLE, RUNMAN: đọc thêm isReverseActive
				switch (e->type)
				{
				case PANTHER:
				case EAGLE:
				case RUNMAN:
				{
					ifile >> value;
					obj->value.push_back(value);
					break;
				}
				}
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

		// Viết ra file grid và xoá các object sau khi có thông số
		std::ofstream ofile;
		ofile.open(gridFileName);
		ofile << colCell << " " << rowCell << " " << objs.size();

		for (auto o : objs)
		{
			ofile << "\n" << o->type << "\n";
			for (auto v : o->value)
			{
				ofile << v << " ";
			}
			ofile << "\n" << o->leftCell << " " << o->topCell << " " << o->rightCell << " " << o->bottomCell;
			delete o;
		}

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
	sprintf_s(gridFileName, "Resources\\Texts\\grid%d.txt", level);

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
	std::unordered_set<Rect*> grounds;

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
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
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
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
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
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
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

			// Xác định ground xuất hiện cho các enemy ở đất
			switch (enemy->type)
			{
			case SWORDMAN:
			case CLOAKMAN:
			case GUNMAN:
			case PANTHER:
			case RUNMAN:
			case BAZOKAMAN:
			case BOSS:
				enemy->DetectGround(this->GetColliableGrounds(enemy));
				break;
			}

			// Xác định hướng active cho các Enemy Panther, Eagle, Runman
			switch (enemy->type)
			{
			case PANTHER:
			{
				ifile >> value;
				auto panther = (EnemyPanther*)enemy;
				panther->activeDistance = (value ? ENEMY_PANTHER_ACTIVE_DISTANCE : -ENEMY_PANTHER_ACTIVE_DISTANCE);
				break;
			}
			case EAGLE:
			{
				ifile >> value;
				auto eagle = (EnemyEagle*)enemy;
				eagle->activeDistance = (value ? ENEMY_EAGLE_ACTIVE_DISTANCE : -ENEMY_EAGLE_ACTIVE_DISTANCE);
				break;
			}
			case RUNMAN:
			{
				ifile >> value;
				auto runman = (EnemyRunMan*)enemy;
				runman->activeDistance = (value ? ENEMY_RUNMAN_ACTIVE_DISTANCE : -ENEMY_RUNMAN_ACTIVE_DISTANCE);
				break;
			}
			}

			ifile >> left >> top >> right >> bottom;
			for (int r = bottom; r <= top; ++r)
			{
				if (r < 0 || r >= rows) continue;
				for (int c = left; c <= right; ++c)
				{
					if (c < 0 || c >= columns) continue;
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

Grid::~Grid()
{
	std::unordered_set<Object*> objs;
	std::unordered_set<Wall*> walls;
	std::unordered_set<Rect*> grounds;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			for (auto o : cells[i][j]->objects)
			{
				objs.insert(o);
			}

			for (auto w : cells[i][j]->walls)
			{
				walls.insert(w);
			}

			for (auto g : cells[i][j]->grounds)
			{
				grounds.insert(g);
			}

			cells[i][j]->objects.clear();
			cells[i][j]->walls.clear();
			cells[i][j]->grounds.clear();
			delete cells[i][j];
		}
		cells[i].clear();
	}
	cells.clear();

	for (auto o : objs)
	{
		o = nullptr;
	}

	for (auto g : grounds)
	{
		delete g;
	}

	for (auto w : walls)
	{
		delete w;
	}
}

void Grid::Update()
{
	this->viewPort = Rect(camera->x, camera->y + Cell::height, camera->width, camera->height + Cell::height);
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
			if (!e->GetSpawnRect().IsContain(viewPort))
			{
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
	if (obj->tag == ENEMY)
	{
		auto e = (Enemy*)obj;
		if (e->isOutScreen)
		{
			return;
		}
	}

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

	if (!(oldLeftCell < 0 || oldRightCell >= columns || oldTopCell >= rows || oldBottomCell < 0))
	{
		if (LeftCell < oldLeftCell)
		{
			if (oldTopCell < rows)
			{
				cells[oldTopCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell && oldBottomCell >= 0)
			{
				cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);
			}
		}

		if (RightCell > oldRightCell)
		{
			if (oldTopCell < rows)
			{
				cells[oldTopCell][oldRightCell]->RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell && oldBottomCell >= 0)
			{
				cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (TopCell < oldTopCell)
		{
			if (oldLeftCell >= 0)
			{
				cells[oldTopCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell && oldRightCell < columns)
			{
				cells[oldTopCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (BottomCell > oldBottomCell)
		{
			if (oldLeftCell >= 0)
			{
				cells[oldBottomCell][oldLeftCell]->RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell && oldRightCell < columns)
			{
				cells[oldBottomCell][oldRightCell]->RemoveObject(obj);
			}
		}

		if (TopCell < rows)
		{
			if (LeftCell >= 0)
			{
				cells[TopCell][LeftCell]->objects.insert(obj);
			}

			if (LeftCell != RightCell && RightCell < columns)
			{
				cells[TopCell][RightCell]->objects.insert(obj);
			}
		}

		if (BottomCell < rows)
		{
			if (LeftCell >= 0)
			{
				cells[BottomCell][LeftCell]->objects.insert(obj);
			}

			if (LeftCell != RightCell && RightCell < columns)
			{
				cells[BottomCell][RightCell]->objects.insert(obj);
			}
		}
	}
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

	for (int r = 0; r < rows; ++r)
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
						respawnObjects.insert(e);
						continue;
					}
					else if (!(e->isActive || e->isOutScreen))
					{
						e->ChangeState(RUNNING);
						e->isReverse = (player->posX < e->posX);
						e->vx = (e->isReverse ? -e->speed : e->speed);
					}

					if (e->isActive)
					{
						setObjects.insert(e);
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
						i->DetectGround(this->GetVisibleGrounds());
						setObjects.insert(i);
						this->AddObject(i);
						this->respawnObjects.insert(h);
						continue;
					}
					else setObjects.insert(o);
					break;
				}

				case WEAPON: case ITEM: case BULLET:
				{
					if (o->isDead)
					{
						it = c->objects.erase(it);
						this->RemoveObject(o);
						delete o;
						continue;
					}
					else setObjects.insert(o);
					break;
				}
				}
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
						if (e->GetSpawnRect().IsContain(viewPort))
						{
							e->isOutScreen = true;
							respawnObjects.insert(e);
						}
						else
						{
							this->MoveObject(e, e->spawnX, e->spawnY);
						}
						continue;
					}
					break;
				}

				case ITEM: case BULLET:
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

std::unordered_set<Wall*> Grid::GetColliableWalls(Object * obj)
{
	std::unordered_set<Wall*> walls;

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
			for (auto w : cells[y][x]->walls)
			{
				walls.insert(w);
			}
		}
	}
	return walls;
}

std::unordered_set<Rect*> Grid::GetColliableGrounds(Object * obj)
{
	std::unordered_set<Rect*> grounds;

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
			for (auto g : cells[y][x]->grounds)
			{
				grounds.insert(g);
			}
		}
	}
	return grounds;
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
				switch (o->tag)
				{
				case ENEMY:
				{
					auto e = (Enemy*)o;
					if (e->isActive && e->StateName != DEAD)
					{
						objs.insert(e);
					}
					break;
				}
				case BULLET:
				{
					auto b = (Bullet*)o;
					if (b->StateName != DEAD)
					{
						objs.insert(b);
					}
					break;
				}
				default:
				{
					objs.insert(o);
					break;
				}
				}
			}
		}
	}
	return objs;
}

void Grid::AddObject(Object * obj)
{
	if (obj == NULL) return;

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