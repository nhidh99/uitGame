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
	int numSetTiles;
	int** mapTiles;
	Tag mapLevel;

public:
	Map(int level);
	void Update();
	void Render();

	Camera* camera;
	int width;
	int height;
	Rect rect;
};