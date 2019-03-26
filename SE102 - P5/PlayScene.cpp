#include "PlayScene.h"

PlayScene::PlayScene()
{
	_player = new Player();
	_camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	_map = MapFactory::GetInstance()->GetMap(0);

	_camera->posX = _map->width >> 1;
	_camera->posY = _map->height >> 1;

	_player->posX = SCREEN_WIDTH >> 1;
	_player->posY = SCREEN_HEIGHT >> 1;
	_player->item = _map->item;

	_map->camera = _camera;

	_leftEdge = _camera->width >> 1;
	_rightEdge = _map->width - (_camera->width >> 1);
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
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
	CameraUpdate(dt);

	for (auto i : _map->objects)
	{
		Collision::GetInstance()->SweptAABB(_player->GetBoundingBox(_camera->posX, _camera->posY), i->GetBoundingBox());
	}
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	_map->Render();
	_player->Render();
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