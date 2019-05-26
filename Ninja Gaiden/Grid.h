#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include <unordered_set>
#include <vector>
#include "Camera.h"
#include "Cell.h"
#include "WeaponFactory.h"
#include "HolderFactory.h"
#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "Player.h"
#include <fstream>

class Grid
{
private:
	int rows;
	int columns;
	Rect viewPort;

	struct GameObject
	{
		int topCell, bottomCell, leftCell, rightCell;
		char type;
		std::vector<int> value;
	};

public:
	void CreateGridFile(int level);
	Grid(int level);
	std::vector<std::vector<Cell*>> cells;
	std::vector<Cell*> visibleCells;
	std::vector<Object*> respawnObjects;

	void Update();
	void RespawnEnemies();

	void MoveObject(Object* obj, float posX, float posY);
	void RemoveObject(Object* obj);
	void AddObject(Object* obj);
	void UpdateVisibleCells();

	std::unordered_set<Object*> GetVisibleObjects();
	std::unordered_set<Wall*> GetVisibleWalls();
	std::unordered_set<Rect*> GetVisibleGrounds();
	std::unordered_set<Object*> GetColliableObjects(Object* obj);
};