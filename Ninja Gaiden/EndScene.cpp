#include "EndScene.h"

EndScene::EndScene()
{
	background = SpriteFactory::GetInstance()->GetSprite(ENDSCENE, 0);
	gameLevel = 0;
	isEndGame = false;
	scoreboard->score = 0;
	scoreboard->bossHealth = ENEMY_BOSS_HEALTH;
	player->SetEnergy(0);
	player->SetWeapon(NONE);
}

EndScene::~EndScene()
{
}

void EndScene::Render()
{
	background->Render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30);
}

void EndScene::OnKeyDown(int key)
{
	if (key == DIK_RETURN)
	{
		SceneManager::GetInstance()->ReplaceScene(new IntroScene());
	}
}
