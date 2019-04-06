#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);
	map->camera = camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	player->item = _map->item;
	player->posX = 50;
	player->posY = SCREEN_HEIGHT >> 1;
	player->ChangeState(new PlayerStandingState());

	camera->posX = SCREEN_WIDTH >> 1;
	camera->posY = map->height >> 1;

	int groundx[18] = { 0,580,644,708,772,804,836, 1026,1125,1409, 1444,1474,1603,1665,1729,1800,1280,1216 };
	int groundy[18] = { 160,154,154,154,154,120,90,154,160,120,90,58,154,154,154,160,90,90 };
	int groundw[18] = { 540,32,32,32, 32,32,128,66,280,30,30,65,18,18,18,255,96,32 };

	int wallx[5] = { 800,832,1410,1442,1474 };
	int wally[5] = { 115,85,115,85,48 };

	// Tạo mảng các vùng đất
	for (int i = 0; i < 18; ++i)
	{
		grounds.push_back(BoundingBox(groundx[i], groundy[i], groundw[i], 1));
	}

	for (int i = 0; i < 5; ++i)
	{
		walls.push_back(BoundingBox(wallx[i], wally[i], 32, 32));
	}

	player->curGroundBound = grounds[0];
}

PlayScene::~PlayScene()
{
}

void PlayScene::CameraUpdate()
{
	camera->posX = player->posX;

	// Đưa các vùng đất đang hiển thị trên màn hỉnh vào mảng
	visibleGrounds.clear();
	for (auto g : grounds)
	{
		if (!(camera->GetBound().right < g.x || camera->GetBound().left > g.x + g.width))
		{
			visibleGrounds.push_back(g);
		}
	}

	// ---
	visibleWalls.clear();
	for (auto w : walls)
	{
		if (!(camera->GetBound().right < w.x || camera->GetBound().left > w.x + w.width))
		{
			visibleWalls.push_back(w);
		}
	}

	// Camera về phần trái của map
	if (camera->posX <= camera->width >> 1)
	{
		camera->posX = camera->width >> 1;
		player->posX = max(player->width >> 1, player->posX);
	}

	// Camera về phần phải của map
	else if (camera->posX >= map->width - (camera->width >> 1))
	{
		camera->posX = map->width - (camera->width >> 1);
		player->posX = min(map->width - player->width, player->posX);
	}
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
	CameraUpdate();
	player->CheckOnGround(this->visibleGrounds);
	player->CheckOnWall(this->visibleWalls);
	//map->Update(dt);
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