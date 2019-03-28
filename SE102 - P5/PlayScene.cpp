#include "PlayScene.h"

PlayScene::PlayScene()
{
	_map = MapFactory::GetInstance()->GetMap(0);
	_map->camera = _camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	_player = new Player();
	_player->posX = 50;
	_player->posY = SCREEN_HEIGHT >> 1;
	_player->item = _map->item;

	_camera->posX = SCREEN_WIDTH >> 1;
	_camera->posY = _map->height >> 1;
	_leftCamera = SCREEN_WIDTH >> 1;
	_rightCamera = _map->width - (SCREEN_WIDTH >> 1);
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
}

void PlayScene::CameraUpdate(float dt)
{
	_camera->posX = _player->posX;

	if (_camera->posX <= _leftCamera)
	{
		_camera->posX = _leftCamera;
		_player->posX = max(_player->width >> 1, _player->posX);
	}
	else if (_camera->posX >= _rightCamera)
	{
		_camera->posX = _rightCamera;
		_player->posX = min(_map->width - _player->width, _player->posX);
	}

	_leftScreen = _camera->posX - (SCREEN_WIDTH >> 1);
	_rightScreen = _leftScreen + SCREEN_HEIGHT;
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	for (auto i : _map->objects)
	{
		Collision::GetInstance()->SweptAABB(_player->GetBoundingBox(), i->GetBoundingBox());
	}

	_map->Update(dt);

	_player->Update(dt);

	_player->item->Update(dt, _leftScreen, _rightScreen);
	
	CameraUpdate(dt);
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	_map->Render();
	_player->Render((SCREEN_WIDTH >> 1) - _camera->posX, 0);
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