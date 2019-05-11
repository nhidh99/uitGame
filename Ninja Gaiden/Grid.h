#pragma once
#include "GameGlobal.h"
#include "Collision.h"
#include "Holder.h"
#include <set>
#include <unordered_set>
#include <vector>
#include "Camera.h"
#include "Cell.h"
#include "Loader.h"
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
	void LoadObjects();

	void RespawnEnemies();
	void RestartGame();

	void MoveObject(Object* obj, float posX, float posY);
	void RemoveObject(Object* obj);

	void UpdateVisibleCells();

	std::unordered_set<Object*> GetVisibleObjects();
	std::unordered_set<Rect*> GetVisibleWalls();
	std::unordered_set<Rect*> GetVisibleGrounds();

	void InitGroundCell(Rect* ground);
	void InitWallCell(Rect* wall);
	void InitObjectCell(Object* obj);
};