﻿#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);

	player->spawnX = player->posX = 50;
	player->spawnY = player->posY = SCREEN_HEIGHT >> 1;
	player->ChangeState(new PlayerStandingState());

	camera->posX = SCREEN_WIDTH >> 1;
	camera->posY = SCREEN_HEIGHT >> 1;

	loader = new Loader();
	grid = new Grid(map->rect);
	this->InitCellsInGrid();
}

PlayScene::~PlayScene()
{
}

void PlayScene::InitCellsInGrid()
{
	auto grounds = loader->LoadGroundsBound();
	auto walls = loader->LoadWallsBound();
	auto holders = loader->LoadHolders();
	auto enemies = loader->LoadEnemies();

	for (auto g : grounds) grid->InitGroundCell(g);

	for (auto w : walls) grid->InitWallCell(w);

	for (auto h : holders) grid->InitObjectCell(h);

	for (auto e : enemies) grid->InitObjectCell(e);
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	map->Update();
	grid->Update();
	this->UpdateObjects(dt);
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

	auto p = player;
	p->Update(dt, std::vector<Object*>());
	p->CheckGroundCollision(grid->GetVisibleGrounds());
	p->CheckWallCollision(grid->GetVisibleWalls());
	grid->MovePlayer(p, p->posX + p->dx, p->posY + p->dy);
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	auto transX = (SCREEN_WIDTH >> 1) - camera->posX;

	map->Render(transX);

	for (auto o : visibleObjects)
	{
		o->Render(transX);
	}

	player->Render(transX);
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