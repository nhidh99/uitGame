#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	sprite = SpriteFactory::GetInstance()->GetSprite(ENEMY, 11);
	tag = ENEMY;
	type = BULLET;
	this->height = ITEM_BULLET_HEIGHT;
	this->width = ITEM_BULLET_WIDTH;
	this->isOnScreen = false;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update(float dt, Rect camRect)
{
	if (isOnScreen)
	{
		posX += vx * dt;
	}
}

void EnemyBullet::Render(float translateX, float translateY)
{
	if (isOnScreen)
	{
		camera->ConvertPositionToViewPort(posX, posY);
		sprite->isReverse = this->isReverse;
		sprite->Render(posX, posY, translateX, translateY);
	}
}

bool EnemyBullet::isOutCam(Rect camRect)
{
	/*if (this->posX <= camRect.x || this->posX >= camRect.y || this->posY <= camRect.y + camRect.height || this->posX >= camRect.x + camRect.width)
	{
		return true;
	}
	return false;*/
	return false;
}

