#include "Map.h"
#include "SpriteFactory.h"

Map::Map(int level)
{
	std::ifstream ifile;
	char fileName[30];
	sprintf_s(fileName, "Resources\\matrix%d.txt", level + 1);
	ifile.open(fileName);
	_mapLevel = Tag(MAP1 + level);

	// Lấy thông tin hàng, cột và chiều dài, rộng của Map tương ứng
	ifile >> _numSetTiles;
	ifile >> _columns;
	ifile >> _rows;
	width = _columns << 4;
	height = _rows << 4;

	// Tải các Sprite tương ứng của map vào Factry
	for (int i = 0; i < _numSetTiles; ++i)
	{
		SpriteFactory::GetInstance()->AddSprite(new Sprite(_mapLevel, i << 4, 0, (i + 1) << 4, 16));
	}

	// Tạo ma trận tương ứng của Map đang xét
	_mapTiles = new int*[_rows];
	for (int r = 0; r < _rows; ++r)
	{
		_mapTiles[r] = new int[_columns];
		for (int c = 0; c < _columns; ++c)
		{
			ifile >> _mapTiles[r][c];
		}
	}
	ifile.close();

	// Cài đặt Quadtree
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	quadtree = new QuadTree(1, rect);

	// Init Shuriken
	item = new ObjectItemShuriken();

	// Init Objects
	for (int i = 0; i < 10; ++i)
	{
		ObjectItemShuriken* shuriken = new ObjectItemShuriken();
		shuriken->posX = (width >> 1) - i * 100;
		shuriken->posY = (height >> 1) - i * 10;
		shuriken->vx = 0;
		shuriken->vy = 0;
		shuriken->isOnScreen = true;
		objects.push_back(shuriken);
	}
}

void Map::Update(float dt)
{
	for (auto i : objects)
	{
		i->Update(dt);
	}
}

void Map::Render()
{
	auto trans = D3DXVECTOR2((SCREEN_WIDTH >> 1) - camera->posX, 0);

	for (auto r = 0; r < _rows; ++r)
	{
		for (auto c = 0; c < _columns; ++c)
		{
			Sprite* sprite = SpriteFactory::GetInstance()->GetSprite(_mapLevel, _mapTiles[r][c]);
			RECT objBound;
			objBound.left = (c << 4);
			objBound.right = objBound.left + TILE_SIZE;
			objBound.top = (r << 4);
			objBound.bottom = objBound.top + TILE_SIZE;

			if (IsContain(objBound, camera->GetBound()))
			{
				sprite->Render(objBound.left + (TILE_SIZE >> 1), objBound.top + (TILE_SIZE>>1), trans.x, trans.y);
			}
		}
	}

	for (auto i : objects)
	{
		i->Render(trans.x, trans.y);
	}

	item->Render(trans.x, trans.y);
}

bool Map::IsContain(RECT rect1, RECT rect2)
{
	return !(rect1.top > rect2.bottom || rect1.bottom < rect2.top || rect1.left > rect2.right || rect1.right < rect2.left);
}
