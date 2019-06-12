#pragma once
#include "ItemBlueSpirit.h"
#include "ItemRedSpirit.h"
#include "ItemGlassHour.h"
#include "ItemRedBag.h"
#include "ItemBlueBag.h"
#include "ItemFireWheel.h"
#include "ItemBlueShuriken.h"
#include "ItemRedShuriken.h"
#include "ItemRedPotion.h"

class ItemFactory
{
public:
	ItemFactory() {};
	~ItemFactory() {};

	static Item* CreateItem(int type)
	{
		switch (type)
		{
		case 1:
			return new ItemBlueSpirit();
		case 2:
			return new ItemRedSpirit();
		case 3:
			return new ItemGlassHour();
		case 4:
			return new ItemBlueShuriken();
		case 5:
			return new ItemRedBag();
		case 6:
			return new ItemFireWheel();
		case 7:
			return new ItemBlueBag();
		case 8:
			return new ItemRedPotion();
		case 9:
			return new ItemRedShuriken();
		default:
			return NULL;
		}
	}
};