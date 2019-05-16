#pragma once
#include "Item.h"

class ItemFireWheel : public Item
{
public:
	ItemFireWheel()
	{
		this->type = FIREWHEEL;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 5);
	}
};