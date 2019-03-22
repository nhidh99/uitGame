#pragma once
#include "GameGlobal.h"
#include <fstream>
#include <map>
#include "Sprite.h"
#include "Camera.h"

class Map
{
private:
	int _columns;
	int _rows;
	int _numSetTiles;
	int** _mapTiles;
	Tag _mapLevel;

public:
	Map(int level);
	void Render();
	bool IsContain(RECT rect1, RECT rect2);

	Camera* camera;
	int width;
	int height;
};