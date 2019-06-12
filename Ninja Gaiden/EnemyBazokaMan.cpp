#include "EnemyBazokaMan.h"

EnemyBazokaMan::EnemyBazokaMan()
{
	animations[STANDING] = new Animation(ENEMY, 3, 3);
	animations[RUNNING] = new Animation(ENEMY, 3, 3);
	animations[ATTACKING] = new Animation(ENEMY, 3, 4);
	type = BAZOKAMAN;
	height = ENEMY_BAZOKAMAN_HEIGHT;
	width = ENEMY_BAZOKAMAN_WIDTH;
	delayTime = ENEMY_BAZOKAMAN_DELAY_TIME >> 1;
	bullets = bulletCount = BULLET_BAZOKAMAN_COUNT;
	speed = vx = vy = 0;
	explodeBullet = SpriteFactory::GetInstance()->GetSprite(BULLET, 5);
}

void EnemyBazokaMan::UpdateDistance(float dt)
{
	this->isReverse = (player->posX < this->posX);
	delayTime -= dt;

	if (StateName == RUNNING && delayTime <= 0)
	{
		this->ChangeState(ATTACKING);
		delayTime = ENEMY_BAZOKAMAN_DELAY_TIME;
	}
}

void EnemyBazokaMan::Update(float dt)
{
	Enemy::Update(dt);
	if (this->isDead)
	{
		delayTime = ENEMY_CLOAKMAN_DELAY_TIME >> 1;
	}
}

void EnemyBazokaMan::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;
	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY + SCREEN_TRANSLATEY);

	if (this->StateName == ATTACKING && this->curAnimation->CurFrameIndex == 1)
	{
		this->explodeBullet->isReverse = this->isReverse;
		this->explodeBullet->Render(posX + (isReverse ? -15 : 15), posY - 10 + SCREEN_TRANSLATEY);
	}
}
