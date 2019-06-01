#pragma once
#include "GameGlobal.h"
#include "Object.h"
#include <unordered_set>

class Cell
{
private:
	int xID, yID;

public:
	Rect rect;
	static int width, height;
	std::unordered_set<Object*> objects;
	std::vector<Wall*> walls;
	std::vector<Rect*> grounds;

	Cell(int xID, int yID);
	~Cell();
	bool IsContain(Rect r);
	void RemoveObject(Object* obj);
};
