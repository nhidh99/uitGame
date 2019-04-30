#include "PlayScene.h"

PlayScene::PlayScene()
{
	map = MapFactory::GetInstance()->GetMap(0);
	map->camera = camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	player->posX = 50;
	player->posY = SCREEN_HEIGHT >> 1;
	player->ChangeState(new PlayerStandingState());

	camera->posX = SCREEN_WIDTH >> 1;
	camera->posY = map->height >> 1;

	loader = new Loader();
	enemyFactory = EnemyFactory::GetInstance();

	grid = new Grid(map->rect);
	grid->InitBoundsCell(loader->LoadGroundsBound(), loader->LoadWallsBound());
	grid->InitHoldersCell(loader->LoadHolders());
	grid->InitEnemiesCell(loader->LoadEnemies());
}

PlayScene::~PlayScene()
{
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	camera->Update(map->rect);
	map->Update();

	auto cameraRect = camera->GetRect();
	grid->Update(cameraRect);

	visibleObjects = grid->GetVisibleObjects(cameraRect);

	for (auto o : visibleObjects)
	{
		if (o->tag == ENEMY)
		{
			enemyFactory->ChangeEnemy(o)->Update(dt, grid->cells);
		}
		else if (o->tag == HOLDER)
		{
			auto h = (Holder*)o;
			h->Update(dt);
		}
	}

	player->Update(dt, std::vector<Object*>());
	player->CheckOnGround(grid->GetVisibleGrounds(cameraRect));
	player->CheckOnWall(grid->GetVisibleWalls(cameraRect));
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	map->Render();

	auto transX = (SCREEN_WIDTH >> 1) - camera->posX;

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