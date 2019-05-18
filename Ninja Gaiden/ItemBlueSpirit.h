#pragma once
#include "Item.h"

class ItemBlueSpirit : public Item
{
public:
	ItemBlueSpirit()
	{
		this->type = BLUESPIRIT;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 0);
	}
};