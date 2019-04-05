#include "PlayScene.h"

PlayScene::PlayScene()
{
	_map = MapFactory::GetInstance()->GetMap(0);
	_map->camera = _camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	player->item = _map->item;
	player->posX = 250;
	player->posY = SCREEN_HEIGHT >> 1;
	player->ChangeState(new PlayerStandingState());

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

	player->curGroundBound = grounds[0];

	
	this->LoadResources(SWORDMAN);
}

PlayScene::~PlayScene()
{
}

void PlayScene::CameraUpdate()
{
	_camera->posX = player->posX;

	if (_camera->posX <= _leftCamera)
	{
		_camera->posX = _leftCamera;
		player->posX = max(player->width >> 1, player->posX);
	}
	else if (_camera->posX >= _rightCamera)
	{
		_camera->posX = _rightCamera;
		player->posX = min(_map->width - player->width, player->posX);
	}

	_leftScreen = _camera->posX - (SCREEN_WIDTH >> 1);
	_rightScreen = _leftScreen + SCREEN_HEIGHT;
}

void PlayScene::LoadResources(EnemyType type)
{
	//Lấy filePath
	std::string filePath;
	switch (type) {
	case SWORDMAN:
		filePath = "Resources\\Swordman.txt";
		break;
	default:
		break;
	}

	std::ifstream ifile;
	ifile.open(filePath);

	//Đọc số lượng đối tượng
	float nums;
	ifile >> nums;

	for (float i = 0; i < nums; i++)
	{
		switch (type)
		{
		case SWORDMAN:
		{
			SwordMan* sw = new SwordMan();

			//Đọc các posX, posY, isReverse
			float pos;
			ifile >> pos;
			sw->posX = pos;
			ifile >> pos;
			sw->posY = pos;

			ifile >> pos;
			if (pos == 0)
				sw->isReverse = false;
			else
				sw->isReverse = true;
			_enemies.push_back(sw);
			break;
		}
		default:
			break;
		}
	}
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	player->CheckOnGround(this->grounds);
	//_map->Update(dt);
	CameraUpdate();

	player->Update(dt, std::vector<Object*>());


	for (auto i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Update(dt);
	}
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	_map->Render();
	player->Render((SCREEN_WIDTH >> 1) - _camera->posX, 0);

	for (auto i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Render((SCREEN_WIDTH >> 1) - _camera->posX, 0);
	}
}

// Xử lí Scene khi nhấn phím
void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	player->OnKeyDown(key);
}

// Xử lí Scene khi thả phím
void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	player->OnKeyUp(key);
}