#include "HolderButterfly.h"

HolderButterfly::HolderButterfly()
{
	curAnimation = new Animation(HOLDER, 0, 1, 75);
	type = BUTTERFLY;
	width = HOLDER_BUTTERFLY_WIDTH;
	height = HOLDER_BUTTERFLY_HEIGHT;
	vx = vy = 0;
}

HolderButterfly::~HolderButterfly()
{
}