#pragma once
#include "HolderItem.h"

class HolderItemBlueShuriken : public HolderItem
{
public:
	HolderItemBlueShuriken()
	{
		sprite = SpriteFactory::GetInstance()->GetSprite(HOLDER, 3);
		type = BLUESHURIKEN;
		this->width = HOLDER_ITEM_BLUESHURIKEN_WIDTH;
		this->height = HOLDER_ITEM_BLUESHURIKEN_HEIGHT;
		this->vx = 0;
		this->vy = 0.02;
	};
	~HolderItemBlueShuriken() {};
};