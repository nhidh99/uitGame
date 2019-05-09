#include "ObjectItemDagger.h"

ObjectItemDagger::ObjectItemDagger()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 15);
	tag = ITEM;
	type = DAGGER;
	vx = -0.03;
	vy = 0.06;
	this->height = ITEM_DAGGER_HEIGHT;
	this->width = ITEM_DAGGER_WIDTH;
	this->isOnScreen = false;
}

ObjectItemDagger::~ObjectItemDagger()
{
}

void ObjectItemDagger::Update(float dt, int maxHigh, int leftScreen, int rightScreen)
{
	if (isOnScreen)
	{
		float dx = vx * dt;
		float dy = vy * dt;

		if (posY < maxHigh)
		{
			vy = -0.06;
		}

		posX += dx;
		posY += dy;

		if (posX > rightScreen || posX < leftScreen)
			isOnScreen = false;
	}
}

void ObjectItemDagger::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		auto posX = this->posX + translateX;
		auto posY = this->posY + translateY;
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

