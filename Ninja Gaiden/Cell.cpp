#include "Cell.h"

int Cell::width = SCREEN_WIDTH >> 1;
int Cell::height = SCREEN_HEIGHT >> 1;

Cell::Cell(int xID, int yID)
{
	this->xID = xID;
	this->yID = yID;
	rect.x = xID * (SCREEN_WIDTH >> 1);
	rect.y = yID * (SCREEN_HEIGHT >> 1);
	rect.width = SCREEN_WIDTH >> 1;
	rect.height = SCREEN_HEIGHT >> 1;
}

Cell::~Cell()
{
}

bool Cell::IsContain(Rect r)
{
	return rect.IsContain(r);
}

void Cell::RemoveObject(Object * obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}