#include "EnemyDagger.h"

EnemyDagger::EnemyDagger()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 15);
	tag = ENEMY;
	type = DAGGER;
	vx = -0.04;
	vy = 0.07;
	this->height = ITEM_DAGGER_HEIGHT;
	this->width = ITEM_DAGGER_WIDTH;
	this->isOnScreen = false;
}

EnemyDagger::~EnemyDagger()
{
}

void EnemyDagger::Update(float dt)
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

		/*if (isOutCam(camRect))
			this->isOnScreen = false;*/
	}
}

void EnemyDagger::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

bool EnemyDagger::isOutCam(Rect camRect)
{
	if (this->posY >= SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

