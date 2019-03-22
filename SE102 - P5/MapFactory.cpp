#include "MapFactory.h"

MapFactory* MapFactory::_instance = NULL;

void MapFactory::LoadResources()
{
	for (int i = 0; i < NUMBER_MAP_LEVEL; ++i)
	{
		_maps.push_back(new Map(i));
	}
}

Map * MapFactory::GetMap(int level)
{
	return _maps[level];
}

MapFactory * MapFactory::GetInstance()
{
	if (_instance == NULL)
		_instance = new MapFactory();
	return _instance;
}