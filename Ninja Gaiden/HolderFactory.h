#pragma once
#include "ItemFactory.h"
#include "HolderButterfly.h"

class HolderFactory
{
public:
	HolderFactory() {};
	~HolderFactory() {};

	static Holder* CreateHolder(int holderID, int itemID)
	{
		Holder* h;

		switch (holderID)
		{
		case 1:
		{
			h = new HolderButterfly();
			break;
		}
		default:
			return NULL;
		}
		
		h->itemID = itemID;
		return h;
	}

	static Holder* ConvertToHolder(Object* o)
	{
		Holder* h = (Holder*)o;

		switch (h->type)
		{
		case BUTTERFLY:
		{
			h = (HolderButterfly*)o;
			break;
		}
		}
		return h;
	}
};