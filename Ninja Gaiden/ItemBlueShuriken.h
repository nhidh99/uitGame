#pragma once
#include "Item.h"

class ItemBlueShuriken : public Item
{
public:
	ItemBlueShuriken()
	{
		this->type = BLUESHURIKEN;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 3);
	}
};