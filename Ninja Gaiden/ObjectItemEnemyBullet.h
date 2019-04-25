#pragma once
#include "ObjectItem.h"
#include "ObjectItemSprite.h"

class ObjectItemEnemyBullet : public ObjectItem {
public:
	ObjectItemSprite* _sprite;
	ObjectItemEnemyBullet();

};