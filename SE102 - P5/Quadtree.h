#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "Camera.h"
#include "Object.h"

class QuadTree
{
private:
	QuadTree **_nodes;
	int GetIndex(RECT body);
	void Split();
	bool IsContain(Object *Object);

public:
	QuadTree(int level, RECT bound);
	std::vector<Object*> Objects;
	int Level;
	RECT Bound;
	void Clear();
	void InsertObject(Object* obj);
	void GetAllObjects(std::vector<Object*> &objects);
	int GetTotalObjects();
};