#include "IntroScene.h"

IntroScene::IntroScene()
{
	game_nameSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 0);
	game_infoSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 1);
	ninjaSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 3);
	stageSprite = SpriteFactory::GetInstance()->GetSprite(INTROSCENE, 2);

	vx = 0.1;
	vy = 0.02;

	game_nameSprite->posX = 100;
	game_nameSprite->posY = 20;

	game_infoSprite->posX = 120;
	game_infoSprite->posY = 300;

	ninjaSprite->posX = 400;
	ninjaSprite->posY = 100;

	stageSprite->posX = 600;
	stageSprite->posY = 100;
}

IntroScene::~IntroScene()
{

}

void IntroScene::Render()
{

	game_nameSprite->ScaleRender(game_nameSprite->posX, game_nameSprite->posY, 0.7, 0.7);

	game_infoSprite->ScaleRender(game_infoSprite->posX, game_infoSprite->posY, 0.7, 0.7);

	ninjaSprite->ScaleRender(ninjaSprite->posX, ninjaSprite->posY, 0.7, 0.7);

	stageSprite->ScaleRender(stageSprite->posX, stageSprite->posY, 0.7, 0.7);
}

void IntroScene::Update(float dt)
{
	if (game_nameSprite->posX >= 120)
	{
		game_nameSprite->posX = 120;
	}
	else
	{
		game_nameSprite->posX += vx * dt;
	}

	if (game_infoSprite->posY <= 200)
	{
		game_infoSprite->posY = 200;
	}

	if (ninjaSprite->posX <= 60)
	{
		ninjaSprite->posX = 60;
	}
	else
		ninjaSprite->posX -= vx * dt;

	if (stageSprite->posX <= 180)
	{
		stageSprite->posX = 180;
	}
	else
	{
		stageSprite->posX -= vx * dt;

	}

	if (game_nameSprite->posX == 120)
	{
		game_infoSprite->posY -= vy * dt;
	}
}

void IntroScene::OnKeyDown(int key)
{
	if (key == DIK_RETURN)
	{
		SceneManager::GetInstance()->ReplaceScene(new PlayScene(1));
	}
}
