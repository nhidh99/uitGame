#include "Cell.h"

int Cell::width = SCREEN_WIDTH >> 1;
int Cell::height = SCREEN_HEIGHT >> 1;

Cell::Cell(int xID, int yID)
{
	this->xID = xID;
	this->yID = yID;
	rect.x = xID * (SCREEN_WIDTH >> 1);
	rect.y = yID * (SCREEN_HEIGHT >> 1);
	width = rect.width = SCREEN_WIDTH >> 1;
	height = rect.height = SCREEN_HEIGHT >> 1;
}

bool Cell::IsContain(Rect r)
{
	return !(rect.x + rect.width < r.x || rect.x > r.x + r.width || rect.y + rect.height < r.y || rect.y > r.y + r.height);
}
