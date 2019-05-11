#pragma once
#include "GameGlobal.h"
#include "SpriteFactory.h"
#include "Camera.h"
#include <fstream>

class Map
{
private:
	int cBegin;
	int cEnd;
	int columns;
	int rows;
	int** mapTiles;
	Tag mapLevel;

public:
	Map(int level);
	void Update();
	void Render();

	int width;
	int height;
	Rect rect;
};