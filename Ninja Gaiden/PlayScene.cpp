#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);
	grid = new Grid(map->rect);
	grid->LoadObjects();

	player->spawnX = player->posX = 50;
	player->spawnY = player->posY = 50;
	player->ChangeState(new PlayerStandingState());

	camera->x = 0;
	camera->y = SCREEN_HEIGHT;
}

PlayScene::~PlayScene()
{
}

void PlayScene::InitCellsInGrid()
{
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	this->UpdateScene();
	this->UpdateObjects(dt);
	this->UpdatePlayer(dt);
}

void PlayScene::UpdateScene()
{
	camera->x = player->posX - (camera->width >> 1);
	map->Update();
	grid->Update();
}

void PlayScene::UpdateObjects(float dt)
{
	visibleObjects.clear();
	visibleObjects = grid->GetVisibleObjects();

	for (auto o : visibleObjects)
	{
		switch (o->tag)
		{
		case ENEMY:
		{
			EnemyFactory::ConvertToEnemy(o)->Update(dt);
			grid->MoveObject(o, o->posX + o->dx, o->posY + o->dy);
			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->Update(dt);
			break;
		}
		}
	}
}

void PlayScene::UpdatePlayer(float dt)
{
	auto p = player;
	p->Update(dt, std::vector<Object*>());
	p->CheckGroundCollision(grid->GetVisibleGrounds());
	p->CheckWallCollision(grid->GetVisibleWalls());

	p->posX += p->dx;
	p->posY += p->dy;

	if (p->posY + (p->width >> 1) < 0)
	{
		grid->RestartGame();
		p->posX = p->spawnX;
		p->posY = p->spawnY;
	}
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	map->Render();

	for (auto o : visibleObjects)
	{
		o->Render();
	}

	player->Render();
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