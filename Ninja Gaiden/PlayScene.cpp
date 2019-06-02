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

	if (isFrozenEnemies)
	{
		frozenEnemiesTime -= dt;
		if (frozenEnemiesTime <= 0)
		{
			isFrozenEnemies = false;
			frozenEnemiesTime = ENEMY_FROZEN_TIME;
		}
	}
}

void PlayScene::UpdateScene()
{
	camera->x = player->posX - (camera->width >> 1);
	map->Update();
	grid->Update();
}

void PlayScene::UpdateVisibleObjects()
{
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		if ((*it)->tag != WEAPON)
		{
			it = visibleObjects.erase(it);
		}
		else ++it;
	}

	for (auto o : grid->GetVisibleObjects())
	{
		visibleObjects.insert(o);
	}
}

void PlayScene::UpdateObjects(float dt)
{
	this->UpdateVisibleObjects();

	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		auto o = *it;
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
			HolderFactory::ConvertToHolder(o)->Update(dt);
			break;
		}
		case ITEM:
		{
			Item* i = (Item*)o;
			i->Update(dt);
			grid->MoveObject(i, i->posX, i->posY + i->dy);
			break;
		}
		case WEAPON:
		{
			auto w = WeaponFactory::ConvertToWeapon(o);
			w->Update(dt, grid->GetColliableObjects(w));

			if (w->isDead || !w->IsCollide(camera->GetRect()))
			{
				w->isDead = true;
				it = visibleObjects.erase(it);
				player->allow[THROWING] = true;
				continue;
			}
			break;
		}
		}
		++it;
	}
}

void PlayScene::UpdatePlayer(float dt)
{
	auto p = player;
	p->rect = p->GetRect();

	p->Update(dt, grid->GetColliableObjects(p));
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

	if (p->isThrowing)
	{
		Weapon* weapon = WeaponFactory::CreateWeapon(p->weaponID);
		weapon->posX = p->posX + (p->isReverse ? -5 : 5);
		weapon->posY = p->posY + 5;
		if (p->isReverse) weapon->vx = -weapon->vx;
		visibleObjects.insert(weapon);
		p->isThrowing = false;
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