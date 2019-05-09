#include "Player.h"

Player* Player::_instance = NULL;

Player::Player()
{
	// Tải các Animation cho Player
	_animations[STANDING] = new Animation(PLAYER, 0);
	_animations[RUNNING] = new Animation(PLAYER, 1, 3, DEFAULT_TPS >> 1);
	_animations[SITTING] = new Animation(PLAYER, 4, 4);
	_animations[JUMPING] = new Animation(PLAYER, 5, 8, DEFAULT_TPS >> 2);
	_animations[FALLING] = new Animation(PLAYER, 5, 8, DEFAULT_TPS >> 2);
	_animations[ATTACKING_STAND] = new Animation(PLAYER, 9, 11, DEFAULT_TPS >> 1);
	_animations[ATTACKING_SIT] = new Animation(PLAYER, 12, 14, DEFAULT_TPS >> 1);
	_animations[CLINGING] = new Animation(PLAYER, 15);
	_animations[CLIMBING] = new Animation(PLAYER, 15, 16);
	_animations[DEAD] = new Animation(PLAYER, 5);
	_animations[INJURED] = new Animation(PLAYER, 5);

	// Allow một số state cho trạng thái khởi đầu (Standing)
	allow[JUMPING] = true;
	allow[ATTACKING] = true;
	allow[MOVING] = true;

	// Các thông số Object
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;

	// Trang bị (kiếm)
	sword = new ObjectItemSword();
}

// Destructor
Player::~Player()
{
	if (curAnimation) delete curAnimation;
	if (sword) delete sword;
	if (item) delete item;

	for (auto it = _animations.begin(); it != _animations.end(); ++it)
	{
		if (it->second) delete it->second;
		_animations.erase(it);
	}
}

Player* Player::GetInstance()
{
	if (_instance == NULL)
		_instance = new Player();
	return _instance;
}

void Player::Update(float dt, std::vector<Object*> ColliableObjects)
{
	curAnimation->Update(dt);

	state->Update(dt);

	dx = (allow[MOVING] ? vx * dt : 0);
	dy = vy * dt;

	/*std::vector<CollisionResult> ResultCollisions;
	ResultCollisions.clear();

	for (auto obj : ColliableObjects)
	{
		auto result = Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), obj->GetBoundingBox());
		if (result.isCollide)
		{
			ResultCollisions.push_back(result);
		}
	}

	if (!ResultCollisions.size())
	{
		Object::Update(dt);
	}
	else
	{
		float minEntryTimeX = 1.0f;
		float minEntryTimeY = 1.0f;
		int nx = 0, ny = 0;

		for (auto result : ResultCollisions)
		{
			if (result.entryTime < minEntryTimeX)
			{
				minEntryTimeX = result.entryTime;
				nx = result.nx;
			}

			if (result.entryTime < minEntryTimeY)
			{
				minEntryTimeY = result.entryTime;
				ny = result.ny;
			}
		}*/

		/*posX += (minEntryTimeX * dx + nx * 2.0f);
		posY += (minEntryTimeY * dy);*/

		//if (nx != 0)
		//{
		//	vx = (vx > 0) ? -0.05 : 0.05;
		//	this->allow[CLINGING] = true;
		//}

		/*if (ny != 0)
		{
			this->vy = 0;
		}*/
		/*}*/
}

// Duyệt tìm lại vùng đất va chạm của player khi ra khỏi vùng hiện tại
// Dùng cách nâng sàn Collision duyệt trước
bool Player::DetectGround(std::unordered_set<Rect*> grounds)
{
	auto tg = curGroundBound;
	auto r = this->GetRect();
	tg.y += this->height;

	if (r.IsContain(tg))
		return true;

	for (auto g : grounds)
	{
		tg = *g;
		tg.y += this->height;

		if (r.IsContain(tg))
		{
			curGroundBound = *g;
			return true;
		}
	}
	return false;
}

// Duyệt tìm tường va chạm
// Bằng cách dịch tường và duyệt trước
bool Player::DectectWall(std::unordered_set<Rect*> walls)
{
	auto tw = curWallBound;
	auto r = GetRect();

	this->vx > 0 ? tw.x -= this->width : tw.x += this->width;
	if (r.IsContain(tw))
		return true;

	for (auto w : walls)
	{
		tw = *w;
		this->vx > 0 ? tw.x -= this->width : tw.x += this->width;

		if (r.IsContain(tw))
		{
			curWallBound = *w;
			return true;
		}
	}
	return false;
}

// Xử lí va chạm với mặt đất theo các vùng đất hiển thị
void Player::CheckGroundCollision(std::unordered_set<Rect*> grounds)
{
	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy < 0)
		{
			auto r = this->GetRect();
			r.y = r.y + dy;
			r.height = r.height - dy;

			if (r.IsContain(curGroundBound))
			{
				this->vy = this->dy = 0;
				if (stateName == ATTACKING_STAND)
					this->allow[MOVING] = false;
			}
		}
	}

	// Nếu không thì đang chạy -> rơi
	else if (this->vy == 0)
	{
		this->ChangeState(new PlayerFallingState());
	}
}

// Kiểm tra va chạm tường
void Player::CheckWallCollision(std::unordered_set<Rect*> walls)
{
	if (this->vx && this->DectectWall(walls))
	{
		auto r = this->GetRect();
		r.x = dx > 0 ? r.x : r.x + dx;
		r.width = dx > 0 ? dx + r.width : r.width - dx;

		if (r.IsContain(curWallBound))
		{
			this->vx = this->dx = 0;
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
	curAnimation->Render(posX, posY);
	sword->Render(posX, posY, curAnimation->CurFrameIndex);
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
			AttackWith(SWORD);
		}
		break;

		// Phím S: tấn công với item
	case DIK_S:
		if (allow[ATTACKING] && !item->isOnScreen)
		{
			allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState());
			AttackWith(item->type);
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
	curAnimation = _animations[stateName];
}

// Tấn công với item
void Player::AttackWith(Type item)
{
	switch (item)
	{
	case SWORD:
		if (sword != NULL)
		{
			sword->isReverse = isReverse;
			sword->isOnScreen = true;
		}
		break;

	case SHURIKEN:
		if (item != NULL)
		{
			this->item->isReverse = isReverse;
			this->item->posX = isReverse ? this->posX - 3 : this->posX + 3;
			this->item->posY = this->posY - 8;
			this->item->vx = isReverse ? -ITEM_SHURIKEN_SPEED : ITEM_SHURIKEN_SPEED;
			this->item->isOnScreen = true;
		}
		break;
	}
}