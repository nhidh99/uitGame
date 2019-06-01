#pragma once
#include "Item.h"

class ItemRedShuriken : public Item
{
public:
	ItemRedShuriken()
	{
		this->type = REDSHURIKEN;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 8);
	}
};