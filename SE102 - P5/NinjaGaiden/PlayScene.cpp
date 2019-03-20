#include "PlayScene.h"

PlayScene::PlayScene()
{
	_player = new Player();
	_item = new ObjectItemShuriken();
	_camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	_map = MapFactory::GetInstance()->GetMap(0);

	_player->ChangeItem(_item);
	_player->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);
	_camera->SetPosition(_map->GetWidth() >> 1, SCREEN_HEIGHT >> 1);
	_map->SetCamera(_camera);

	_leftEdge = _camera->GetWidth() >> 1;
	_rightEdge = _map->GetWidth() - (_camera->GetWidth() >> 1);
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
	if (_item) delete _item;
}

void PlayScene::CameraUpdate(float dt)
{
	if (_camera->GetPosX() <= _leftEdge)
	{
		_camera->SetPosX(max(_leftEdge, _camera->GetPosX()));

		_player->AddPosX(_player->GetVx()*dt);
		_player->SetPosX(max(_player->GetWidth() >> 1, _player->GetPosX()));
		if (_player->GetPosX() >= SCREEN_WIDTH >> 1)
		{
			_camera->AddPosX(1);
		}
	}
	else if (_camera->GetPosX() >= _rightEdge)
	{
		_camera->SetPosX(min(_rightEdge, _camera->GetPosX()));

		_player->AddPosX(_player->GetVx()*dt);	
		_player->SetPosX(min(SCREEN_WIDTH - _player->GetWidth(), _player->GetPosX()));
		if (_player->GetPosX() <= SCREEN_WIDTH >> 1)
		{
			_camera->AddPosX(-1);
		}
	}
	else
	{
		_camera->AddPosX(_player->GetVx() * dt);
	}
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	_player->HandleKeyBoard(_keyCode);
	_player->Update(dt);
	_item->Update(dt);
	CameraUpdate(dt);
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	_map->Render();
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