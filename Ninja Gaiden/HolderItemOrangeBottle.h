#pragma once
#include "HolderItem.h"

class HolderItemOrangeBottle : public HolderItem
{
public:
	HolderItemOrangeBottle()
	{
		sprite = SpriteFactory::GetInstance()->GetSprite(HOLDER, 4);
		type = ORANGEBOTTLE;
		this->width = HOLDER_ITEM_ORANGEBOTTLE_WIDTH;
		this->height = HOLDER_ITEM_ORANGEBOTTLE_HEIGHT;
		this->vx = 0;
		this->vy = 0.02;
	}
	~HolderItemOrangeBottle();
};