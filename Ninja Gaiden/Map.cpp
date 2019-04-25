#include "Map.h"
#include "SpriteFactory.h"

auto addCols = (SCREEN_WIDTH >> 4) + 1;

Map::Map(int level)
{
	std::ifstream ifile;
	char fileName[30];
	sprintf_s(fileName, "Resources\\matrix%d.txt", level + 1);
	ifile.open(fileName);
	mapLevel = MAP1;

	// Lấy thông tin hàng, cột và chiều dài, rộng của Map tương ứng
	ifile >> numSetTiles;
	ifile >> columns;
	ifile >> rows;
	width = columns << 4;
	height = rows << 4;
	
	rect.x = rect.y = 0;
	rect.width = width;
	rect.height = height;

	// Tải các Sprite tương ứng của map vào Factry
	for (int i = 0; i < numSetTiles; ++i)
	{
		SpriteFactory::GetInstance()->AddSprite(new Sprite(mapLevel, i << 4, 0, i + 1 << 4, 16));
	}

	// Tạo ma trận tương ứng của Map đang xét
	mapTiles = new int*[rows];
	for (int r = 0; r < rows; ++r)
	{
		mapTiles[r] = new int[columns];
		for (int c = 0; c < columns; ++c)
		{
			ifile >> mapTiles[r][c];
		}
	}
	ifile.close();
}

void Map::Update()
{
	cBegin = max(0, (camera->posX - (camera->width >> 1)) / 16);
	cEnd = min(cBegin + addCols, columns);
}

void Map::Render()
{
	auto transX = (SCREEN_WIDTH >> 1) - (int)camera->posX;
	//auto trans = D3DXVECTOR2((SCREENWIDTH >> 1) - camera->posX, 0);

	for (auto r = 0; r < rows; ++r)
	{
		for (auto c = cBegin; c < cEnd; ++c)
		{
			auto sprite = SpriteFactory::GetInstance()->GetSprite(mapLevel, mapTiles[r][c]);
			sprite->Render((c << 4) + (TILE_SIZE >> 1), (r << 4) + (TILE_SIZE >> 1), transX);
		}
	}
}