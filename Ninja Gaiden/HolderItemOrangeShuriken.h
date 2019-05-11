#pragma once
#include "HolderItem.h"

class HolderItemOrangeShuriken : public HolderItem
{
public:
	HolderItemOrangeShuriken()
	{
		sprite = SpriteFactory::GetInstance()->GetSprite(HOLDER, 5);
		type = ORANGESHURIKEN;
		this->width = HOLDER_ITEM_ORANGESHURIKEN_WIDTH;
		this->height = HOLDER_ITEM_ORANGESHURIKEN_HEIGHT;
		this->vx = 0;
		this->vy = 0.02;
	}
	~HolderItemOrangeShuriken() {};
};