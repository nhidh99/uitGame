#pragma once
#include "Map.h"

class MapFactory
{
private:
	std::vector<Map*> _maps;
	static MapFactory* _instance;

public:
	void LoadResources();
	Map* GetMap(int level);
	static MapFactory* GetInstance();
};