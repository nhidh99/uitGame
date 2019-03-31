#include "Player.h"

// Constructor
Player::Player()
{
	// Load Animations for Player
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

	// Allow State when construct
	allow[JUMPING] = true;
	allow[ATTACKING] = true;

	// Init sword for player
	tag = PLAYER;
	width = PLAYER_WIDTH;
	height = PLAYER_STANDING_HEIGHT;
	sword = new ObjectItemSword();

	// Set state
	_playerHandler = new PlayerHandler();
	_playerHandler->Player = this;
	ChangeState(new PlayerStandingState(_playerHandler));

}

// Destructor
Player::~Player()
{
	if (_playerHandler) delete _playerHandler;
	if (curAnimation) delete curAnimation;
	if (sword) delete sword;
	if (item) delete item;

	for (auto it = _animations.begin(); it != _animations.end(); ++it)
	{
		if (it->second) delete it->second;
		_animations.erase(it);
	}
}

void Player::Update(float dt, std::vector<Object*> ColliableObjects)
{
	curAnimation->Update(dt);

	_playerHandler->State->Update(dt);

	Object::Update(dt);

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

bool Player::IsOnGround()
{
	return !(this->GetBoundingBox().x > curGroundBound.x + curGroundBound.width
		|| this->GetBoundingBox().x + this->width < curGroundBound.x);
}

void Player::CheckOnGround(std::vector<BoundingBox> grounds)
{
	if (this->vy == 0)
	{
		if (!this->IsOnGround())
		{
			curGroundBound = BoundingBox();
			this->ChangeState(new PlayerFallingState(_playerHandler));
		}
		else this->posY = curGroundBound.y - this->height;
	}

	else if (this->vy > 0)
	{
		if (this->IsOnGround() && this->posY > this->curGroundBound.y - this->height)
		{
			this->ChangeState(new PlayerStandingState(_playerHandler));
			return;
		}

		for (auto g : grounds)
		{
			if (Collision::GetInstance()->SweptAABB(this->GetBoundingBox(), g).ny == 1)
			{
				this->ChangeState(new PlayerStandingState(_playerHandler));
				curGroundBound = g;
				return;
			}
		}
	}
}

// Render Player and sword / item if it's on screen
void Player::Render(float translateX, float translateY)
{
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(posX, posY, translateX, translateY);
	sword->Render(posX, posY, curAnimation->CurFrameIndex, translateX, translateY);
}

// Handle KeyDown for state change can change in others
void Player::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		// Attacking State (with sword)
	case DIK_A:
		if (allow[ATTACKING])
		{
			allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState(_playerHandler));
			AttackWith(SWORD);
		}
		break;

		// Attacking State (with item)
	case DIK_S:
		if (allow[ATTACKING] && !item->isOnScreen)
		{
			allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState(_playerHandler));
			AttackWith(item->type);
		}
		break;

		// Attacking State (with swing sword)
	case DIK_D:
		if (state == JUMPING || state == FALLING)
		{
			allow[ATTACKING] = false;
			AttackWith(SWINGSWORD);
		}
		break;

		// Jumping State
	case DIK_SPACE:
		if (allow[JUMPING])
		{
			allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState(_playerHandler));
		}
		break;
	}
}

// Handle keyboard up for state can change in others 
void Player::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		// While KeyDown is Up while attacking
	case DIK_DOWN:
		if (state == SITTING)
			state = STANDING;
		break;
	}
}

// Change State 
void Player::ChangeState(PlayerState * newState)
{
	state = newState->StateName;
	_playerHandler->SetState(newState);
	curAnimation = _animations[state];
}

// Attack with item
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

		/*case SWINGSWORD:
			if (swingSword != NULL)
			{
				swingSword->isReverse = isReverse;
				swingSword->isOnScreen = true;
			}
			break;*/

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