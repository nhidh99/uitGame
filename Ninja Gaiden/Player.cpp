#include "Player.h"

Player* Player::_instance = NULL;

Player::Player()
{
	// Tải các Animation cho Player
	animations[STANDING] = new Animation(PLAYER, 0);
	animations[RUNNING] = new Animation(PLAYER, 1, 3, DEFAULT_TPS >> 1);
	animations[SITTING] = new Animation(PLAYER, 4, 4);
	animations[JUMPING] = new Animation(PLAYER, 5, 8, DEFAULT_TPS >> 2);
	animations[FALLING] = new Animation(PLAYER, 5, 8, DEFAULT_TPS >> 2);
	animations[ATTACKING_STAND] = new Animation(PLAYER, 9, 11, DEFAULT_TPS >> 1);
	animations[ATTACKING_SIT] = new Animation(PLAYER, 12, 14, DEFAULT_TPS >> 1);
	animations[CLINGING] = new Animation(PLAYER, 15);
	animations[CLIMBING] = new Animation(PLAYER, 15, 16, DEFAULT_TPS >> 1);
	animations[DEAD] = new Animation(PLAYER, 5);
	animations[INJURED] = new Animation(PLAYER, 5);

	// Các thông số Object
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
}

// Destructor
Player::~Player()
{
	if (curAnimation) delete curAnimation;

	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
}

Player* Player::GetInstance()
{
	if (_instance == NULL)
		_instance = new Player();
	return _instance;
}

void Player::Respawn()
{
	this->allow[JUMPING] = true;
	this->allow[ATTACKING] = true;
	this->allow[MOVING] = true;
	this->allow[THROWING] = true;
	this->isAttacking = false;
	this->isThrowing = false;
	this->SetHealth(PLAYER_HEALTH);
	this->SetEnergy(0);
	this->SetWeapon(NONE);
	this->vx = this->vy = this->dx = this->dy = 0;
	this->posX = this->spawnX;
	this->posY = this->spawnY;
	this->isDead = false;
	this->isReverse = false;
	this->ChangeState(new PlayerStandingState());
}

void Player::DetectSpawnY(std::unordered_set<Rect*> grounds)
{
	this->groundBound = Rect();

	for (auto g : grounds)
	{
		if (g->x < this->spawnX && this->spawnX < g->x + g->width
			&& g->y >= groundBound.y && this->spawnY > g->y)
		{
			groundBound = *g;
		}
	}
	this->spawnY = this->posY = groundBound.y + (this->height >> 1);
}

void Player::Update(float dt, std::unordered_set<Object*> ColliableObjects)
{
	if (this->posY + (this->height >> 1) <= 0)
	{
		this->isDead = true;
		return;
	}

	curAnimation->Update(dt);
	state->Update(dt);

	CollisionResult result;
	result.isCollide = false;
	result.nx = result.ny = 0;
	result.entryTime = 1.0f;

	for (auto obj : ColliableObjects)
	{
		switch (obj->tag)
		{
		case ENEMY:
		case BULLET:
		{
			if (this->stateName != INJURED)
			{
				auto r = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), obj->GetBoundingBox());
				if (r.isCollide)
				{
					result = r;
					break;
				}
			}
			break;
		}

		case ITEM:
		{
			if (this->GetRect().IsContain(obj->GetRect()))
			{
				obj->isDead = true;
				Sound::getInstance()->play("item");

				switch (obj->type)
				{
				case BLUESPIRIT:
				{
					this->SetEnergy(energy + 5);
					break;
				}
				case REDSPIRIT:
				{
					this->SetEnergy(energy + 10);
					break;
				}
				case GLASSHOUR:
				{
					isFrozenEnemies = true;
					frozenEnemiesTime = ENEMY_FROZEN_TIME;
					frozenCount = ENEMY_FROZEN_TIME_COUNT;
					break;
				}

				case BLUESHURIKEN:
				case FIREWHEEL:
				case REDSHURIKEN:
				{
					this->SetWeapon(obj->type);
					break;
				}
				}
			}
			break;
		}
		}
	}

	if (!result.isCollide || stateName == INJURED)
	{
		dx = (allow[MOVING] ? vx * dt : 0);
		dy = vy * dt;
	}
	else
	{
		Sound::getInstance()->play("injured");
		this->isReverse = (result.nx == 1);
		this->SetHealth(--health);
		this->ChangeState(new PlayerInjuredState());
	}
}

// Duyệt tìm lại vùng đất va chạm của player khi ra khỏi vùng hiện tại
// Dùng cách nâng sàn Collision duyệt trước
bool Player::DetectGround(std::unordered_set<Rect*> grounds)
{
	auto rbp = this->GetRect();					//rect broading-phase
	auto bottom = rbp.y - rbp.height;
	rbp.y = rbp.y + dy;
	rbp.height = rbp.height - dy;

	if (rbp.IsContain(groundBound) && (bottom >= groundBound.y))
		return true;

	for (auto g : grounds)
	{
		if (rbp.IsContain(*g) && (bottom >= g->y))
		{
			groundBound = *g;
			return true;
		}
	}
	return false;
}

// Duyệt tìm tường va chạm
// Bằng cách dịch tường và duyệt trước
bool Player::DetectWall(std::unordered_set<Wall*> walls)
{
	bool flag = false;
	auto r = this->GetRect();
	r.x = dx > 0 ? r.x : r.x + dx;
	r.width = dx > 0 ? dx + r.width : r.width - dx;

	if (r.IsContain(wallBound.rect))
	{
		flag = true;
	}
	else
	{
		for (auto w : walls)
		{
			if (w->rect.IsContain(r))
			{
				wallBound = *w;
				flag = true;
				break;
			}
		}
	}
	return flag;
}

// Xử lí va chạm với mặt đất theo các vùng đất hiển thị
void Player::CheckGroundCollision(std::unordered_set<Rect*> grounds)
{
	if (this->isOnWall) return;

	// Trên không
	if (this->vy)
	{
		this->isOnGround = false;
	}

	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy < 0)
		{
			this->isOnGround = true;
			this->vy = this->dy = 0;
			this->posY = groundBound.y + (this->height >> 1);

			if (stateName == ATTACKING_STAND)
				this->allow[MOVING] = false;
		}
	}

	// Nếu không thì đang chạy -> rơi
	else if (!this->vy)
	{
		this->ChangeState(new PlayerFallingState());
	}
}

// Kiểm tra va chạm tường
void Player::CheckWallCollision(std::unordered_set<Wall*> walls)
{
	if (this->isOnWall) return;

	if (this->vx && this->DetectWall(walls))
	{
		float wallLeft = wallBound.rect.x;
		float wallRight = wallLeft + wallBound.rect.width;
		float playerLeft = this->posX - (this->width >> 1);
		float playerRight = this->posX + (this->width >> 1);

		if (this->vx > 0 && playerRight > wallLeft && playerRight < wallRight)
		{
			this->vx = this->dx = 0;
			this->posX = wallLeft - (this->width >> 1);

			if (wallBound.type && this->vy
				&& this->posY + (this->height >> 1) <= wallBound.rect.y
				&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			{
				Sound::getInstance()->play("jump");
				this->isReverse = false;
				this->ChangeState(new PlayerClingingState());
			}
		}
		else if (this->vx < 0 && playerLeft < wallRight && playerLeft > wallLeft)
		{
			this->vx = this->dx = 0;
			this->posX = wallRight + (this->width >> 1);

			if (wallBound.type && this->vy
				&& this->posY + (this->height >> 1) <= wallBound.rect.y
				&& this->posY - (this->height >> 1) >= wallBound.rect.y - wallBound.rect.height)
			{
				Sound::getInstance()->play("jump");
				this->isReverse = true;
				this->ChangeState(new PlayerClingingState());
			}
		}
	}
}

// Render nhân vật (bản chất là Render Animation và vũ khí)
void Player::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;
	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY + SCREEN_TRANSLATEY);
}

// Xử lí nhấn phím (chung cho các State)
void Player::OnKeyDown(int key)
{
	if (key == DIK_Z)
	{
		isFrozenEnemies = true;
		frozenEnemiesTime = ENEMY_FROZEN_TIME;
		frozenCount = ENEMY_FROZEN_TIME_COUNT;
	}

	if (this->stateName == INJURED) return;

	switch (key)
	{
		// Phím X: tấn công với vũ khí
	case DIK_X:
	{
		if (!keyCode[DIK_UP])
		{
			if (allow[ATTACKING])
			{
				allow[ATTACKING] = false;
				Sound::getInstance()->play("attack");
				ChangeState(new PlayerAttackingState());
				this->isAttacking = true;
			}
		}
		else
		{
			if (allow[THROWING] && weaponType != NONE && !this->isOnWall
				&& this->stateName != ATTACKING_SIT && this->stateName != ATTACKING_STAND)
			{
				switch (this->weaponType)
				{
				case BLUESHURIKEN:
				{
					if (this->energy >= 3)
					{
						this->SetEnergy(energy - 3);
						break;
					}
					else return;
				}

				case FIREWHEEL:
				case REDSHURIKEN:
				{
					if (this->energy >= 5)
					{
						this->SetEnergy(energy - 5);
						break;
					}
					else return;
				}
				}
				allow[THROWING] = false;
				Sound::getInstance()->play("attack");
				this->isThrowing = true;
				ChangeState(new PlayerAttackingState());
			}
		}
		break;
	}

		// Phím C: nhảy
	case DIK_C:
		if (allow[JUMPING])
		{
			Sound::getInstance()->play("jump");
			allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState());
		}
		break;
	}
}

// Xử lí sự kiện thả phím (dùng chung cho các State)
void Player::OnKeyUp(int keyCode)
{
	if (this->stateName == INJURED) return;

	switch (keyCode)
	{
		// Khi thả phím DOWN: state hiện tại chuyển thành đứng
	case DIK_DOWN:
		if (stateName == SITTING)
			stateName = STANDING;
		break;
	}
}

// Đổi State
void Player::ChangeState(PlayerState * newState)
{
	delete state;
	state = newState;
	stateName = newState->StateName;
	curAnimation = animations[stateName];
}

void Player::SetHealth(int health)
{
	this->health = health;
	scoreboard->playerHealth = health;

	if (this->health == 0)
	{
		this->isDead = true;
	}
}

void Player::SetWeapon(Type weaponType)
{
	this->weaponType = weaponType;
	scoreboard->playerWeapon = weaponType;
}

void Player::SetEnergy(int energy)
{
	this->energy = energy;
	scoreboard->playerEnergy = energy;
}
