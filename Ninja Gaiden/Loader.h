#pragma once
#include "EnemyFactory.h"
#include "HolderButterfly.h"
#include "HolderItemFactory.h"
#include <string>
#include <fstream>
#include <vector>

class Loader
{
public:
	Loader() {};
	~Loader() {};
	std::vector<Holder*> LoadHolders();
	std::vector<Enemy*> LoadEnemies();
	std::vector<Rect*> LoadWallsBound();
	std::vector<Rect*> LoadGroundsBound();
};