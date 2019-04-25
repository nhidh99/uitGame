#pragma once
#include "GameGlobal.h"
#include <fstream>
#include "Sprite.h"
#include "Camera.h"
#include "Collision.h"
#include "Object.h"
#include "ObjectItemShuriken.h"

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