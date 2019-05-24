#include "EnemyEagle.h"

EnemyEagle::EnemyEagle()
{
	animations[STANDING] = new Animation(ENEMY, 17, 17, 150);
	animations[ATTACKING] = new Animation(ENEMY, 17, 18, 150);
	type = EAGLE;
	height = ENEMY_EAGLE_HEIGHT;
	width = ENEMY_EAGLE_WIDTH;
	delayTime = 1000;
}

EnemyEagle::~EnemyEagle()
{
}

void EnemyEagle::UpdateDistance(float dt)
{
	if (delayTime <= 0)
	{
		this->isReverse = (player->posX < this->posX);
		this->dx = 1.5 * (player->posX - this->posX) / MAX_FRAME_RATE;
		this->dy = 1.5 * (player->posY - this->posY) / MAX_FRAME_RATE;
		delayTime = 1000;
	}
	else
	{
		delayTime -= dt;
	}
}