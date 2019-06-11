#include "PlayScene.h"

PlayScene::PlayScene(int level)
{
	map = MapFactory::GetInstance()->GetMap(level);
	grid = new Grid(level);

	delayStart = 3000;
	gameLevel = level;
	isFrozenEnemies = false;

	p = player;
	p->posX = p->spawnX = 50;
	p->posY = p->spawnY = 50;
	p->DetectSpawnY(grid->GetColliableGrounds(p));
	p->Respawn();

	camera->x = 0;
	camera->y = SCREEN_HEIGHT;
	scoreboard->stage = gameLevel;

	char soundFileName[10];

	if (!delayEnd)
	{
		sprintf_s(soundFileName, "stage%d", gameLevel);
		Sound::getInstance()->setVolume(90.0f, soundFileName);
		Sound::getInstance()->play(soundFileName, true);
	}

	if (gameLevel > 1)
	{
		sprintf_s(soundFileName, "stage%d", gameLevel - 1);
		Sound::getInstance()->stop(soundFileName);
	}

	switch (gameLevel)
	{
	case 1:
		endPoint = 1950;
		break;

	case 2:
		endPoint = 3050;
		break;

	case 3:
		endPoint = 300;
		break;
	}
}

PlayScene::~PlayScene()
{
	if (grid) delete grid;
}

bool PlayScene::PlayerIsOnAirGround()
{
	if (gameLevel == 2)
	{
		float airGroundX[5] = { 1153,1282,1376,1473,1565 };
		for (int i = 0; i < 5; ++i)
		{
			if (p->groundBound.x == airGroundX[i])
				return true;
		}
		return false;
	}
	return false;
}

// Update các thông số các đối tượng trong Scene
void PlayScene::Update(float dt)
{
	if (delayRestart)
	{
		delayRestart -= dt;
		if (delayRestart <= 0)
		{
			delayRestart = 0;
			this->RestartScene();
		}
		return;
	}

	this->UpdateScene();

	if (delayStart)
	{
		delayStart -= dt;
		this->UpdateVisibleObjects();

		if (delayStart <= 0)
		{
			delayStart = 0;
		}
		return;
	}

	this->UpdateScoreboard(dt);
	this->UpdateObjects(dt);
	this->UpdatePlayer(dt);

	if (isFrozenEnemies)
	{
		if (frozenEnemiesTime / 1000 == frozenCount)
		{
			Sound::getInstance()->play("glasshour");
			--frozenCount;
		}

		frozenEnemiesTime -= dt;
		if (frozenEnemiesTime <= 0)
		{
			isFrozenEnemies = false;
		}
	}

	if (p->posX >= endPoint)
	{
		delayEnd = 2000;
		Sound::getInstance()->play("win");
		SceneManager::GetInstance()->ReplaceScene(new PlayScene(gameLevel + 1));
	}
}

void PlayScene::UpdateScoreboard(float dt)
{
	scoreboard->Update(dt);
	if (!scoreboard->timer && !isEndGame)
	{
		this->SetRestartScene();
	}
}

void PlayScene::UpdateScene()
{
	camera->x = p->posX - (camera->width >> 1);
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
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		auto o = *it;
		switch (o->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)o;
			e->Update(dt);
			grid->MoveObject(e, e->posX + e->dx, e->posY + e->dy);

			switch (e->type)
			{
			case CLOAKMAN:
			case GUNMAN:
			case BAZOKAMAN:
			{
				if (e->IsFinishAttack())
				{
					auto b = BulletFactory::CreateBullet(e->type);
					b->isReverse = e->isReverse;
					if (b->isReverse) b->vx = -b->vx;
					b->posX = e->posX + (e->isReverse ? -5 : 5);
					b->posY = e->posY + 3;
					b->ChangeState(ACTIVE);
					grid->AddObject(b);
					e->bulletCount--;

					if (e->bulletCount == 0)
					{
						e->bulletCount = e->bullets;
						e->ChangeState(RUNNING);
					}
				}
				break;
			}
			case PANTHER:
			{
				auto p = (EnemyPanther*)e;
				if (!p->isOnGround)
				{
					p->vy = -0.12f;
					p->DetectCurGround(grid->GetVisibleGrounds());
				}
				break;
			}
			case RUNMAN:
			{
				auto r = (EnemyRunMan*)e;
				if (!r->isOnGround)
				{
					r->DetectCurGround(grid->GetColliableGrounds(r));
				}
				break;
			}
			case BOSS:
			{
				auto boss = (EnemyBoss*)e;
				if (boss->bulletCountdown == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						auto b = BulletFactory::CreateBullet(BOSS);
						b->vx = e->isReverse ? -BULLET_BOSS_SPEED : BULLET_BOSS_SPEED;
						b->posX = e->posX + (e->isReverse ? 15 * i : -15 * i);
						b->posY = e->posY + (i - 1) * 20;
						b->ChangeState(ACTIVE);
						grid->AddObject(b);
					}
					boss->bulletCountdown = 3;
				}
			}
			}
			break;
		}

		case HOLDER:
		{
			auto h = (Holder*)o;
			h->Update(dt);
			break;
		}
		case ITEM:
		{
			Item* i = (Item*)o;
			i->Update(dt);
			grid->MoveObject(i, i->posX, i->posY + i->dy);
			break;
		}
		case BULLET:
		{
			Bullet* b = (Bullet*)o;
			b->Update(dt);
			grid->MoveObject(b, b->posX + b->dx, b->posY + b->dy);
			break;
		}

		case WEAPON:
		{
			auto w = WeaponFactory::ConvertToWeapon(o);

			if (w->isDead || !w->IsCollide(camera->GetRect())
				|| (w->type == SWORD && p->stateName != ATTACKING_STAND
					&& p->stateName != ATTACKING_SIT))
			{
				it = visibleObjects.erase(it);
				delete w;
				continue;
			}

			w->Update(dt, grid->GetColliableObjects(w));
			break;
		}
		}
		++it;
	}
	this->UpdateVisibleObjects();
}

void PlayScene::UpdatePlayer(float dt)
{
	if (p->isDead)
	{
		this->SetRestartScene();
		return;
	}

	p->Update(dt, grid->GetColliableObjects(p));
	p->CheckGroundCollision(grid->GetColliableGrounds(p));

	if (!this->PlayerIsOnAirGround())
	{
		p->CheckWallCollision(grid->GetColliableWalls(p));
	}

	p->posX += p->dx;
	p->posY += p->dy;

	if (p->isAttacking)
	{
		Weapon* weapon = WeaponFactory::CreateWeapon(SWORD);
		weapon->isReverse = p->isReverse;
		weapon->posX = p->posX + (p->isReverse ? -22 : 22);
		weapon->posY = p->posY + 8;
		visibleObjects.insert(weapon);
		p->isAttacking = false;
	}

	else if (p->isThrowing)
	{
		Weapon* weapon = WeaponFactory::CreateWeapon(p->weaponType);
		weapon->posX = p->posX + (p->isReverse ? -5 : 5);
		weapon->posY = p->posY + 5;
		weapon->isReverse = p->isReverse;
		if (p->isReverse) weapon->vx = -weapon->vx;
		visibleObjects.insert(weapon);
		p->isThrowing = false;
		p->allow[THROWING] = false;
	}
}

void PlayScene::SetRestartScene()
{
	char soundFileName[10];
	sprintf_s(soundFileName, "stage%d", gameLevel);
	Sound::getInstance()->stop(soundFileName);
	Sound::getInstance()->play("over");
	delayRestart = GAME_RESTART_DELAY;
}

void PlayScene::RestartScene()
{
	char soundFileName[10];
	sprintf_s(soundFileName, "stage%d", gameLevel);
	Sound::getInstance()->play(soundFileName);

	p->Respawn();
	p->ChangeState(new PlayerStandingState());

	scoreboard->timer = GAME_TIMER;
	isFrozenEnemies = false;

	for (auto o : grid->respawnObjects)
	{
		switch (o->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)o;
			e->ChangeState(STANDING);
			break;
		}
		case HOLDER:
		{
			auto h = (Holder*)o;
			h->isDead = false;
			break;
		}
		}
		grid->MoveObject(o, o->spawnX, o->spawnY);
	}

	for (auto o : visibleObjects)
	{
		if (o->tag == ENEMY)
		{
			auto e = (Enemy*)o;
			e->ChangeState(STANDING);
			grid->MoveObject(o, o->spawnX, o->spawnY);
		}
	}
	this->visibleObjects.clear();
	grid->respawnObjects.clear();
}

// Tải Scene lên màn hình bằng cách vẽ object có trong trong Scene
void PlayScene::Render()
{
	map->Render();

	scoreboard->Render();

	for (auto o : visibleObjects)
	{
		o->Render();
	}

	p->Render();
}

// Xử lí Scene khi nhấn phím
void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	p->OnKeyDown(key);
}

// Xử lí Scene khi thả phím
void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	p->OnKeyUp(key);
}