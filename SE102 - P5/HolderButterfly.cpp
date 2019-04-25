#include "HolderButterfly.h"

HolderButterfly::HolderButterfly()
{
	curAnimation = new Animation(HOLDER, 0, 1, 75);

	type = BUTTERFLY;
	width = HODLER_BUTTERFLY_WIDTH;
	height = HODLER_BUTTERFLY_HEIGHT;
	vx = 0;
	vy = 0;
}

HolderButterfly::~HolderButterfly()
{
}

