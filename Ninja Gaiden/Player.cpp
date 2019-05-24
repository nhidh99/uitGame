﻿#include "Player.h"

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
	animations[CLIMBING] = new Animation(PLAYER, 15, 16);
	animations[DEAD] = new Animation(PLAYER, 5);
	animations[INJURED] = new Animation(PLAYER, 5);

	// Allow một số state cho trạng thái khởi đầu (Standing)
	allow[JUMPING] = true;
	allow[ATTACKING] = true;
	allow[MOVING] = true;
	allow[THROWING] = true;

	// Các thông số Object
	weaponType = FIREWHEEL;
	isOnGround = false;
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

void Player::Update(float dt, std::unordered_set<Object*> ColliableObjects)
{
	curAnimation->Update(dt);

	state->Update(dt);

	std::vector<CollisionResult> ResultCollisions;

	for (auto obj : ColliableObjects)
	{
		switch (obj->tag)
		{
		case ENEMY:
		{
			auto e = (Enemy*)obj;
			if (e->StateName == DEAD) continue;

			auto result = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), obj->GetBoundingBox());
			if (result.isCollide)
			{
				ResultCollisions.push_back(result);
			}
			break;
		}

		case ITEM:
		{
			auto i = (Item*)obj;

			if (this->GetRect().IsContain(i->GetRect()))
			{
				i->isDead = true;

				switch (i->type)
				{
				case GLASSHOUR:
					isFrozenEnemies = true;
					frozenEnemiesTime = ENEMY_FROZEN_TIME;
					break;

				case BLUESHURIKEN:
				case FIREWHEEL:
					this->weaponType = i->type;
					break;
				}
			}
		}
		}
	}

	if (!ResultCollisions.size() || stateName == INJURED)
	{
		dx = (allow[MOVING] ? vx * dt : 0);
		dy = vy * dt;
		return;
	}

	float minEntryTimeX = 1.0f;
	//float minEntryTimeY = 1.0f;
	int nx = 0;
	//int ny = 0;

	for (auto result : ResultCollisions)
	{
		if (result.entryTime < minEntryTimeX)
		{
			minEntryTimeX = result.entryTime;
			nx = result.nx;
		}

		/*if (result.entryTime < minEntryTimeY)
		{
			minEntryTimeY = result.entryTime;
			ny = result.ny;
		}*/
	}

	this->isReverse = (nx == 1);
	this->ChangeState(new PlayerInjuredState());
}

// Duyệt tìm lại vùng đất va chạm của player khi ra khỏi vùng hiện tại
// Dùng cách nâng sàn Collision duyệt trước
bool Player::DetectGround(std::unordered_set<Rect*> grounds)
{
	auto r = this->GetRect();
	r.y = r.y + dy;
	r.height = r.height - dy;

	if (r.IsContain(curGroundBound))
		return true;

	for (auto g : grounds)
	{
		if (r.IsContain(*g) && (r.y >= g->y + g->height))
		{
			curGroundBound = *g;
			return true;
		}
	}
	return false;
}

// Duyệt tìm tường va chạm
// Bằng cách dịch tường và duyệt trước
bool Player::DectectWall(std::unordered_set<Wall*> walls)
{
	bool flag = false;
	auto r = this->GetRect();
	r.x = dx > 0 ? r.x : r.x + dx;
	r.width = dx > 0 ? dx + r.width : r.width - dx;

	if (r.IsContain(curWallBound))
	{
		flag = true;
	}
	else
	{
		for (auto w : walls)
		{
			if (w->rect.IsContain(r))
			{
				curWallBound = w->rect;
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
	// Trên không
	if (this->vy)
	{
		this->isOnGround = false;
	}

	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy < 0 && this->GetRect().IsContain(curGroundBound))
		{
			this->isOnGround = true;
			this->vy = this->dy = 0;
			this->posY = curGroundBound.y + (this->height >> 1);
			
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
	if (this->vx && this->DectectWall(walls))
	{
		this->vx = 0;
		this->dx = dx > 0 ? curWallBound.x - (this->posX + (this->width >> 1)) - 1 
			: curWallBound.x + curWallBound.width - (this->posX - (this->width >> 1)) + 1;
	}
}

// Render nhân vật (bản chất là Render Animation và vũ khí)
void Player::Render(float translateX, float translateY)
{
	auto posX = this->posX + translateX;
	auto posY = this->posY + translateY;

	camera->ConvertPositionToViewPort(posX, posY);
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY);
}

// Xử lí nhấn phím (chung cho các State)
void Player::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		// Phím A: tấn công với vũ khí
	case DIK_A:
		if (allow[ATTACKING])
		{
			allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState());
			this->isAttacking = true;
		}
		break;

		// Phím S: tấn công với item
	case DIK_S:
		if (allow[THROWING] && weaponType != NONE 
			&& stateName != ATTACKING_STAND && stateName != ATTACKING_SIT)
		{
			allow[THROWING] = false;
			ChangeState(new PlayerAttackingState());
			this->isThrowing = true;
		}
		break;


		// Phím Space: nhảy
	case DIK_SPACE:
		if (allow[JUMPING])
		{
			allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState());
		}
		break;
	}
}

// Xử lí sự kiện thả phím (dùng chung cho các State)
void Player::OnKeyUp(int keyCode)
{
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