#pragma once
#include "HolderBird.h"
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
		case 2:
		{
			h = new HolderBird();
			break;
		}
		default:
			return NULL;
		}
		
		h->itemID = itemID;
		return h;
	}
};