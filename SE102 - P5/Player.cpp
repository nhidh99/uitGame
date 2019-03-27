#include "Player.h"

// Constructor
Player::Player()
{
	// Load Animations for Player
	_animations[STANDING] = new Animation(PLAYER, 0);
	_animations[RUNNING] = new Animation(PLAYER, 1, 3, TIME_PER_FRAME >> 1);
	_animations[SITTING] = new Animation(PLAYER, 4, 4);
	_animations[JUMPING] = new Animation(PLAYER, 5, 8, TIME_PER_FRAME >> 2);
	_animations[FALLING] = new Animation(PLAYER, 5, 8, TIME_PER_FRAME >> 2);
	_animations[ATTACKING_STAND] = new Animation(PLAYER, 9, 11, TIME_PER_FRAME >> 1);
	_animations[ATTACKING_SIT] = new Animation(PLAYER, 12, 14, TIME_PER_FRAME >> 1);
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
	if (_curAnimation) delete _curAnimation;
	if (sword) delete sword;
	if (swingSword) delete swingSword;
	if (item) delete item;

	for (auto it = _animations.begin(); it != _animations.end(); ++it)
	{
		if (it->second) delete it->second;
		_animations.erase(it);
	}
}

// Update player: Animation, State and Position after delta-time
void Player::Update(float dt)
{
	isLastFrame = _curAnimation->isLastFrame;

	_curAnimation->Update(dt);

	_playerHandler->State->Update(dt);

	posX += vx * dt;

	posY += vy * dt;
}

// Render Player and sword / item if it's on screen
void Player::Render(float translateX, float translateY)
{
	_curAnimation->isReverse = this->isReverse;
	_curAnimation->Render(posX, posY, translateX, translateY);
	sword->Render(posX, posY, _curAnimation->CurFrameIndex, translateX, translateY);
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
	_curAnimation = _animations[state];
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

	case SWINGSWORD:
		if (swingSword != NULL)
		{
			swingSword->isReverse = isReverse;
			swingSword->isOnScreen = true;
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