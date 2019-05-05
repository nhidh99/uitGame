#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include "Holder.h"
#include <set>
#include <unordered_set>
#include <vector>
#include "Camera.h"
#include "Cell.h"
#include "Enemy.h"

class Grid
{
private:
	int rows;
	int columns;
	Rect viewPort;

public:
	Grid(Rect MapRect);
	std::vector<std::vector<Cell*>> cells;
	std::vector<Cell*> visibleCells;
	std::vector<Enemy*> respawnEnemies;

	void Update();
	void RespawnEnemies();
	void MoveObject(Object* obj, float posX, float posY);
	void MovePlayer(Player* obj, float posX, float posY);
	void RemoveObject(Object* obj);
	void UpdateVisibleCells();

	std::unordered_set<Object*> GetVisibleObjects();
	std::set<Rect> GetVisibleWalls();
	std::set<Rect> GetVisibleGrounds();

	void InitHoldersCell(std::vector<Holder*> holders);
	void InitEnemiesCell(std::vector<Enemy*> enemies);
	void InitBoundsCell(std::vector<Rect> grounds, std::vector<Rect> walls);
};