#pragma once
#include "GameGlobal.h"
#include <fstream>
#include <map>
#include "Sprite.h"
#include "Camera.h"

class Map
{
private:
	int _width;
	int _height;
	int _columns;
	int _rows;
	int _numSetTiles;
	int** _mapTiles;
	Tag _mapLevel;
	Camera* _camera;

public:
	Map(int level);
	void Render();
	void SetCamera(Camera* camera);
	int GetWidth();
	int GetHeight();
	bool IsContain(RECT rect1, RECT rect2);
};