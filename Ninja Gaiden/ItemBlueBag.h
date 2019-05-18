#pragma once
#include "Item.h"

class ItemBlueBag : public Item
{
public:
	ItemBlueBag() 
	{
		this->type = BLUEBAG;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 6);
	}
};