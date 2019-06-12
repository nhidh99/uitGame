#include "EndScene.h"

EndScene::EndScene()
{
	background = SpriteFactory::GetInstance()->GetSprite(ENDSCENE, 0);
}

EndScene::~EndScene()
{
}

void EndScene::Render()
{
	background->Render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
