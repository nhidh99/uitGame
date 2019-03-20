#include "PlayScene.h"

PlayScene::PlayScene()
{
	_player = new Player();
	_item = new ObjectItemShuriken();
	_player->ChangeItem(_item);
	_player->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
	if (_item) delete _item;
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	_player->HandleKeyBoard(_keyCode);
	_player->Update(dt);
	_item->Update(dt);
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	_player->Render();
	_item->Render();
}

// Xử lí Scene khi nhấn phím
void PlayScene::OnKeyDown(int keyCode)
{
	_keyCode[keyCode] = true;
	_player->OnKeyDown(keyCode);
}

// Xử lí Scene khi thả phím
void PlayScene::OnKeyUp(int keyCode)
{
	_keyCode[keyCode] = false;
	_player->OnKeyUp(keyCode);
}