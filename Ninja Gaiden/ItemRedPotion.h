#pragma once
#include "Item.h"

class ItemRedPotion : public Item
{
public:
	ItemRedPotion()
	{
		this->type = REDPOTION;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 7);
	}
};