#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);
	grid = new Grid(map->rect);
	grid->LoadObjects();

	player->spawnX = player->posX = 50;
	player->spawnY = player->posY = 100;
	player->ChangeState(new PlayerStandingState());

	camera->x = 0;
	camera->y = SCREEN_HEIGHT;
}

PlayScene::~PlayScene()
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
			Enemy* e = EnemyFactory::ConvertToEnemy(o);
			e->Update(dt);
			grid->MoveObject(o, o->posX + o->dx, o->posY + o->dy);
			break;
		}
		case HOLDER:
		{
			HolderFactory::ConvertToHolder(o)->Update(dt);
			break;
		}
		case ITEM:
		{
			ItemFactory::ConvertToItem(o)->Update(dt);
			grid->MoveObject(o, o->posX, o->posY + o->dy);
			break;
		}
		}
	}
}

void PlayScene::UpdatePlayer(float dt)
{
	auto p = player;
	p->rect = p->GetRect();
	
	p->Update(dt, grid->GetColliableObjects());
	p->CheckGroundCollision(grid->GetVisibleGrounds());
	p->CheckWallCollision(grid->GetVisibleWalls());

	p->posX += p->dx;
	p->posY += p->dy;

	if (p->rect.y < 0)
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
		switch (o->tag)
		{
		case ENEMY:
		{
			EnemyFactory::ConvertToEnemy(o)->Render(0, 0);
			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->Render(0, 0);
			break;
		}
		}
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