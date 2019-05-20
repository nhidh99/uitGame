#include "HolderButterfly.h"

HolderButterfly::HolderButterfly()
{
	animation = new Animation(HOLDER, 0, 1, 75);
	type = BUTTERFLY;
	vx = vy = 0;
}

HolderButterfly::~HolderButterfly()
{
}