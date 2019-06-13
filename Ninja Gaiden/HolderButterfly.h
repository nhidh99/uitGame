#pragma once
#include "Holder.h"

class HolderButterfly : public Holder 
{
public:
	HolderButterfly()
	{
		animation = new Animation(HOLDER, 0, 1, DEFAULT_TPF >> 1);
		type = BUTTERFLY;
		vx = vy = 0;
	}
};