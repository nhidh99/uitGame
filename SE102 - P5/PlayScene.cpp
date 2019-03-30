#include "PlayScene.h"

PlayScene::PlayScene()
{
	_map = MapFactory::GetInstance()->GetMap(0);
	_map->camera = _camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	_player = new Player();
	_player->item = _map->item;
	_player->posX = 50;
	_player->posY = SCREEN_HEIGHT >> 1;

	_camera->posX = SCREEN_WIDTH >> 1;
	_camera->posY = _map->height >> 1;

	_leftCamera = SCREEN_WIDTH >> 1;
	_rightCamera = _map->width - (SCREEN_WIDTH >> 1);

	int groundx[16] = { 0,576,640,704,768,805,832, 1023,1125,1418, 1448,1472,1604,1668,1732,1805 };
	int groundy[16] = { 160,156,156,156,156,122,92,156,160,122,90,58,156,156,156,160 };
	int groundw[16] = { 540,30,30,30,30,30,128,66,280,34,24,65,14,14,14,255 };
	
	/*for (int i = 0; i < 16; ++i)
	{
		ObjectGround* ground = new ObjectGround(groundx[i], groundy[i], groundw[i], groundh[i]);
		grounds.push_back(ground);
	}*/

	for (int i = 0; i < 16; ++i)
	{
		BoundingBox g;
		g.x = groundx[i];
		g.y = groundy[i];
		g.width = groundw[i];
		g.height = 5;
		g.vx = g.vy = 0;
		grounds.push_back(g);
	}

	_player->curGroundBound = grounds[0];
}

PlayScene::~PlayScene()
{
	if (_player) delete _player;
}

void PlayScene::CameraUpdate()
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

BoundingBox curGroundBound;

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	_player->CheckOnGround(this->grounds);
	//_map->Update(dt);
	CameraUpdate();

	_player->Update(dt, std::vector<Object*>());

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