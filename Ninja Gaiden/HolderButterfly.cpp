#include "HolderButterfly.h"

HolderButterfly::HolderButterfly()
{
	curAnimation = new Animation(HOLDER, 0, 1, 75);
	type = BUTTERFLY;
	vx = vy = 0;
}

HolderButterfly::~HolderButterfly()
{
}