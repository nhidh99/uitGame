#pragma once
#include "Item.h"

class  ItemRedBag : public Item
{
public:
	ItemRedBag()
	{
		this->type = REDBAG;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 4);
	}
};