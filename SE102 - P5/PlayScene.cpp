#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);
	map->camera = camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	player->item = map->item;
	player->posX = 50;
	player->posY = SCREEN_HEIGHT >> 1;
	player->ChangeState(new PlayerStandingState());

	camera->posX = SCREEN_WIDTH >> 1;
	camera->posY = map->height >> 1;

	int groundx[18] = { 0,576,640,704,770,802,834, 1023,1125,1409, 1444,1474,1603,1665,1729,1800,1280,1216 };
	int groundy[18] = { 160,154,154,154,154,120,90,154,160,120,90,58,154,154,154,160,90,90 };
	int groundw[18] = { 540,32,32,32, 32,32,128,66,280,30,30,65,18,18,18,255,96,32 };

	// Tạo mảng các vùng đất: nâng tọa độ positionY nhằm tạo trigger xét trước va chạm
	for (int i = 0; i < 18; ++i)
	{
		BoundingBox g;
		g.x = groundx[i];
		g.y = groundy[i];
		g.width = groundw[i];
		g.height = 1;
		g.vx = g.vy = 0;
		grounds.push_back(g);
	}
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

	if (camera->posX <= camera->width >> 1)
	{
		camera->posX = camera->width >> 1;
		player->posX = max(player->width >> 1, player->posX);
	}

	else if (camera->posX >= map->width - (camera->width >> 1))
	{
		camera->posX = map->width - (camera->width >> 1);
		player->posX = min(map->width - player->width, player->posX);
	}
}

// Update các thông số các đối tượng trong Scene

void PlayScene::Update(float dt)
{
	CameraUpdate();
	player->CheckOnGround(this->visibleGrounds);
	//map->Update(dt);
	player->Update(dt, std::vector<Object*>());

}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	map->Render();
	player->Render((SCREEN_WIDTH >> 1) - camera->posX, 0);
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