#include "Map.h"
#include "SpriteFactory.h"

Map::Map(int level)
{
	std::ifstream ifile;
	char fileName[30];
	sprintf_s(fileName, "Resources\\matrix%d.txt", level + 1);
	ifile.open(fileName);
	_mapLevel = MAP1;

	// Lấy thông tin hàng, cột và chiều dài, rộng của Map tương ứng
	ifile >> _numSetTiles;
	ifile >> _columns;
	ifile >> _rows;
	width = _columns << 4;
	height = _rows << 4;
	
	rect.x = rect.y = 0;
	rect.width = width;
	rect.height = height;

	// Tải các Sprite tương ứng của map vào Factry
	for (int i = 0; i < _numSetTiles; ++i)
	{
		SpriteFactory::GetInstance()->AddSprite(new Sprite(_mapLevel, i << 4, 0, i + 1 << 4, 16));
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

	// Init Shuriken
	item = new ObjectItemShuriken();
}

void Map::Update()
{
	_cBegin = max(0, (camera->posX - (camera->width >> 1)) / 16);
	_cEnd = min(_cBegin + (SCREEN_WIDTH >> 4) + 1, _columns);
}

void Map::Render()
{
	auto transX = (SCREEN_WIDTH >> 1) - (int)camera->posX;
	//auto trans = D3DXVECTOR2((SCREEN_WIDTH >> 1) - camera->posX, 0);

	for (auto r = 0; r < _rows; ++r)
	{
		for (auto c = _cBegin; c < _cEnd; ++c)
		{
			auto sprite = SpriteFactory::GetInstance()->GetSprite(_mapLevel, _mapTiles[r][c]);
			sprite->Render(c << 4, r << 4, (TILE_SIZE >> 1) + transX, TILE_SIZE >> 1);
		}
	}
	item->Render(transX, 0);
}