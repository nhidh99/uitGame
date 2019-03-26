#include "Quadtree.h"

int QuadTree::GetIndex(RECT body)
{
	auto halfVerticle = (Bound.right + Bound.left) >> 1;
	auto halfHorizontal = (Bound.bottom - Bound.top) >> 1;

	if (body.top > Bound.top && body.bottom < halfHorizontal)
	{
		//nam phia ben tren
		if (body.left > Bound.left && body.right < halfVerticle)
		{
			//nam phia ben trai
			return 0;
		}
		else if (body.left > halfVerticle && body.right < Bound.right)
		{
			//nam phia ben phai
			return 1;
		}
	}
	else if (body.top > halfHorizontal && body.bottom < Bound.bottom)
	{
		//nam phia ben duoi
		if (body.left > Bound.left && body.right < halfVerticle)
		{
			//nam phia ben trai
			return 2;
		}
		else if (body.left > halfVerticle && body.right < Bound.right)
		{
			//nam phia ben phai
			return 3;
		}
	}
	return -1;
}

void QuadTree::Split()
{
	_nodes = new QuadTree *[4];
	RECT qtBound = RECT();
	auto width = (Bound.right - Bound.left) >> 1;
	auto height = (Bound.bottom - Bound.top) >> 1;

	//phan goc trai tren
	qtBound.left = qtBound.left;
	qtBound.right = qtBound.left + width;
	qtBound.top = qtBound.top;
	qtBound.bottom = qtBound.top + height;
	_nodes[0] = new QuadTree(Level + 1, qtBound);

	//phan goc phai tren
	qtBound.left = qtBound.left + width;
	qtBound.right = qtBound.left + width;
	qtBound.top = qtBound.top;
	qtBound.bottom = qtBound.top + height;
	_nodes[1] = new QuadTree(Level + 1, qtBound);

	//phan goc trai duoi
	qtBound.left = qtBound.left;
	qtBound.right = qtBound.left + width;
	qtBound.top = qtBound.top + height;
	qtBound.bottom = qtBound.top + height;
	_nodes[2] = new QuadTree(Level + 1, qtBound);

	//phan goc phai duoi
	qtBound.left = qtBound.left + width;
	qtBound.right = qtBound.left + width;
	qtBound.top = qtBound.top + height;
	qtBound.bottom = qtBound.top + height;
	_nodes[3] = new QuadTree(Level + 1, qtBound);
}

bool QuadTree::IsContain(Object * obj)
{
	auto rect = obj->GetBound();
	return !(rect.left < Bound.left || rect.right > Bound.right || rect.top < Bound.top || rect.bottom > Bound.bottom);
}

QuadTree::QuadTree(int level, RECT bound)
{
	this->Level = level;
	this->Bound = bound;
}

void QuadTree::Clear()
{
	if (_nodes)
	{
		for (auto i = 0; i < 4; ++i)
		{
			if (_nodes[i])
			{
				_nodes[i]->Clear();
				delete _nodes[i];
				_nodes[i] = nullptr;
			}
		}
		delete[] _nodes;
	}
}

void QuadTree::InsertObject(Object* obj)
{
	auto index = GetIndex(obj->GetBound());

	if (_nodes)
	{
		if (index != -1)
		{
			_nodes[index]->InsertObject(obj);
			return;
		}
	}

	if (index == -1)
	{
		Objects.push_back(obj);
	}

	else
	{
		if (!_nodes)
		{
			this->Split();
		}
		_nodes[index]->InsertObject(obj);
	}
}

void QuadTree::GetAllObjects(std::vector<Object*>& objects)
{
	for (auto child : Objects)
	{
		objects.push_back(child);
	}

	if (_nodes)
	{
		for (auto i = 0; i < 4; ++i)
		{
			_nodes[i]->GetAllObjects(objects);
		}
	}
}

int QuadTree::GetTotalObjects()
{
	auto totalObjects = Objects.size();
	if (_nodes)
	{
		for (int i = 0; i < 4; ++i)
			totalObjects += _nodes[i]->GetTotalObjects();
	}
	return totalObjects;
}
