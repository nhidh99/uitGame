#pragma once
#include "Item.h"

class ItemRedSpirit : public Item
{
public:
	ItemRedSpirit()
	{
		this->type = REDSPIRIT;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 1);
	}
};