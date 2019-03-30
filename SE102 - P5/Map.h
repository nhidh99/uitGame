#pragma once
#include "GameGlobal.h"
#include <fstream>
#include "Sprite.h"
#include "Camera.h"
#include "Quadtree.h"
#include "Object.h"
#include "ObjectGround.h"
#include "ObjectItemShuriken.h"
#include "Player.h"

class Map
{
private:
	int _cBegin;
	int _cEnd;
	int _columns;
	int _rows;
	int _numSetTiles;
	int** _mapTiles;
	Tag _mapLevel;

public:
	Map(int level);
	void Update(float dt);
	void Render();
	bool IsContain(Rect rect1, Rect rect2);

	ObjectItem* item;
	QuadTree* quadtree;
	Camera* camera;
	Player* player;

	int width;
	int height;
};