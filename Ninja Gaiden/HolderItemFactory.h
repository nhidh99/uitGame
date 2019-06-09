#pragma once
#include "HolderItemSandWatch.h"
#include "HolderItemBlueShuriken.h"
#include "HolderItemOrangeBottle.h"
#include "HolderItemOrangeShuriken.h"

class HolderItemFactory {
private:
	static HolderItemFactory* _instance;
public:
	HolderItemFactory() {};
	~HolderItemFactory() {};

	static HolderItemFactory* GetInstance()
	{
		if (_instance == NULL)
			_instance = new HolderItemFactory();
		return _instance;
	}
	HolderItem* CreateHolderItem(int type)
	{
		switch (type)
		{
		case 1:
			return new HolderItemSandWatch();
		case 2:
			return new HolderItemBlueShuriken();
		case 3:
			return new HolderItemOrangeShuriken();
		case 4:
			return new HolderItemOrangeBottle();
		default:
			return NULL;
		}
	}
};