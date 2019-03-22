#include "PlayScene.h"

PlayScene::PlayScene()
{
	_player = new Player();
	_camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	_item = new ObjectItemShuriken();
	_map = MapFactory::GetInstance()->GetMap(0);

	_player->posX = SCREEN_WIDTH >> 1;
	_player->posY = SCREEN_HEIGHT >> 1;
	_player->item = _item;

	_camera->posX = _map->width >> 1;
	_camera->posY = _map->height >> 1;
	_map->camera = _camera;

	_leftEdge = _camera->width >> 1;
	_rightEdge = _map->width - (_camera->width >> 1);
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
	if (_item) delete _item;
}

void PlayScene::CameraUpdate(float dt)
{
	if (_camera->posX <= _leftEdge)
	{
		_camera->posX = max(_leftEdge, _camera->posX);
		_player->posX += _player->vx * dt;
		_player->posX = max(_player->width >> 1, _player->posX);

		if (_player->posX >= SCREEN_WIDTH >> 1)
		{
			_camera->posX++;
		}
	}
	else if (_camera->posX >= _rightEdge)
	{
		_camera->posX = min(_rightEdge, _camera->posX);
		_player->posX += _player->vx * dt;
		_player->posX = min(SCREEN_WIDTH - _player->width, _player->posX);

		if (_player->posX <= SCREEN_WIDTH >> 1)
		{
			_camera->posX--;
		}
	}
	else
	{
		_camera->posX += _player->vx * dt;
	}
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
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
void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	_player->OnKeyDown(key);
}

// Xử lí Scene khi thả phím
void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	_player->OnKeyUp(key);
}