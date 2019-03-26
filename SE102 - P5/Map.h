#pragma once
#include "GameGlobal.h"
#include <fstream>
#include "Sprite.h"
#include "Camera.h"
#include "Quadtree.h"
#include "Object.h"
#include "ObjectItemShuriken.h"
#include "Player.h"

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

	ObjectItem* item;
	QuadTree* quadtree;
	Camera* camera;
	std::vector<ObjectItem*> objects;

	int width;
	int height;
};