#pragma once
#include "Item.h"

class  ItemGlassHour : public Item
{
public:
	ItemGlassHour()
	{
		this->type = GLASSHOUR;
		this->sprite = SpriteFactory::GetInstance()->GetSprite(ITEM, 2);
	}

	void Update(float dt)
	{
		Item::Update(dt);
	}
};