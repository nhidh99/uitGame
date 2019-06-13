#include "IntroScene.h"

IntroScene::IntroScene()
{
	nameSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 0);
	infoSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 1);
	stageSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 2);
	ninjaSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 3);

	vx = 0.25;
	vy = 0.1;

	nameSprite->posX = 100;
	nameSprite->posY = SCREEN_HEIGHT >> 2;

	infoSprite->posX = SCREEN_WIDTH >> 1;
	infoSprite->posY = 300;

	ninjaSprite->posX = 400;
	ninjaSprite->posY = (SCREEN_HEIGHT >> 1) + 30;

	stageSprite->posX = 500;
	stageSprite->posY = (SCREEN_HEIGHT >> 1) + 30;

	Sound::getInstance()->play("intro", true);
}

IntroScene::~IntroScene()
{

}

void IntroScene::Render()
{
	nameSprite->ScaleRender(nameSprite->posX, nameSprite->posY, 0.7, 0.7);
	infoSprite->ScaleRender(infoSprite->posX, infoSprite->posY, 0.7, 0.7);
	ninjaSprite->ScaleRender(ninjaSprite->posX, ninjaSprite->posY, 0.7, 0.7);
	stageSprite->ScaleRender(stageSprite->posX, stageSprite->posY, 0.7, 0.7);
}

void IntroScene::Update(float dt)
{
	if (nameSprite->posX >= SCREEN_WIDTH >> 1)
	{
		nameSprite->posX = SCREEN_WIDTH >> 1;

		infoSprite->posY -= vy * dt;

		if (infoSprite->posY <= 190)
		{
			infoSprite->posY = 190;
		}
	}
	else
	{
		nameSprite->posX += vx * dt;
	}

	if (ninjaSprite->posX <= 90)
	{
		ninjaSprite->posX = 90;
	}
	else ninjaSprite->posX -= vx * dt;

	if (stageSprite->posX <= 160)
	{
		stageSprite->posX = 160;
	}
	else
	{
		stageSprite->posX -= vx * dt;
	}
}

void IntroScene::OnKeyDown(int key)
{
	if (key == DIK_RETURN)
	{
		Sound::getInstance()->stop("intro");
		SceneManager::GetInstance()->ReplaceScene(new PlayScene(1));
	}
}
