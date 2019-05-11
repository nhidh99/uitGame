#pragma once
#include "HolderItem.h"
#include "Sprite.h"

class HolderItemSandWatch : public HolderItem {
public:
	HolderItemSandWatch()
	{
		sprite = SpriteFactory::GetInstance()->GetSprite(HOLDER, 2);
		type = SANDWATCH;
		this->height = HOLDER_ITEM_SANDWATCH_HEIGHT;
		this->width = HOLDER_ITEM_SANDWATCH_WIDTH;
		this->isOnScreen = false;
		this->vx = 0;
		this->vy = 0.02;
	}
	~HolderItemSandWatch() {};
};