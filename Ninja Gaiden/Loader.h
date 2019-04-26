#pragma once
#include "EnemyFactory.h"
#include "HolderButterfly.h"
#include <string>
#include <fstream>
#include <vector>

class Loader
{
private:
	EnemyFactory* enemyFactory;

public:
	Loader();
	~Loader();
	std::vector<Holder*> LoadHolders();
	std::vector<Enemy*> LoadEnemies();
	std::vector<BoundingBox> LoadWallsBound();
	std::vector<BoundingBox> LoadGroundsBound();
	void LoadResources();
};