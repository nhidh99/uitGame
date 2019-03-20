#include "Player.h"

// Constructor khởi tạo các thông số cho Player
Player::Player()
{
	_animations[STANDING] = new Animation(PLAYER, 0, 0);
	_animations[RUNNING] = new Animation(PLAYER, 1, 3);
	_animations[SITTING] = new Animation(PLAYER, 4, 4);
	_animations[JUMPING] = new Animation(PLAYER, 5, 8, TIME_PER_FRAME >> 1);
	_animations[FALLING] = new Animation(PLAYER, 5, 8, TIME_PER_FRAME >> 1);
	_animations[ATTACKING_STAND] = new Animation(PLAYER, 9, 11, TIME_PER_FRAME >> 1);
	_animations[ATTACKING_SIT] = new Animation(PLAYER, 12, 14, TIME_PER_FRAME >> 1);
	_animations[CLINGING] = new Animation(PLAYER, 15, 15);
	_animations[CLIMBING] = new Animation(PLAYER, 15, 16);
	_animations[DEAD] = new Animation(PLAYER, 5, 5);
	_animations[INJURED] = new Animation(PLAYER, 5, 5);

	_allow[JUMPING] = true;
	_allow[ATTACKING] = true;
	_allow[CLINGING] = false;

	_sword = new ObjectItemSword();
	_swingsword = new ObjectItemSwingSword();

	_playerHandler = new PlayerHandler();
	_playerHandler->SetPlayer(this);
	ChangeState(new PlayerStandingState(_playerHandler));

	_width = _curAnimation->GetWidth();
	_height = _curAnimation->GetHeight();
	_isReverse = false;
}

// Destructor
Player::~Player()
{
	if (_playerHandler) delete _playerHandler;
	if (_curAnimation) delete _curAnimation;

	for (auto it = _animations.begin(); it != _animations.end(); ++it)
	{
		if (it->second) delete it->second;
		_animations.erase(it);
	}
}

// Update các thông số của Player sau khoảng delta-time
// Gồm: Update Animation hiện tại, State hiện tại, tọa độ (theo Object) và Item (nếu có)
void Player::Update(float dt)
{
	_curAnimation->Update(dt);

	_playerHandler->GetState()->Update(dt);

	Object::Update(dt);

	_posX = min(max((_width >> 1), _posX), SCREEN_WIDTH - (_width));
}

// Render Player (kèm Item nếu có) lên màn hình
void Player::Render()
{
	_curAnimation->FlipHorizontal(_isReverse);
	_curAnimation->Render(_posX, _posY);

	if (_sword->IsOnScreen())
	{
		_sword->Render(_posX, _posY, _curAnimation->GetCurIndex());
	}

	else if (_swingsword->IsOnScreen())
	{
		_swingsword->Render(_posX, _posY, _curAnimation->GetCurIndex());
	}
}

// Vùng hình chữ nhật chứa Player trên màn hình (với tâm Player ở giữa)
RECT Player::GetBound()
{
	RECT bound;
	bound.left = _posX - (_curAnimation->GetWidth() >> 1);
	bound.right = bound.left + _curAnimation->GetWidth();
	bound.top = _posY - (_curAnimation->GetHeight() >> 1);
	bound.bottom = bound.top + _curAnimation->GetHeight();
	return bound;
}

// Xử lí sự kiện bàn phím của State tương ứng của Player
void Player::HandleKeyBoard(std::map<int, bool> keyCode)
{
	_playerHandler->GetState()->HandleKeyboard(keyCode);
}

// Xử lí sự kiện nhấn phím cho Player
void Player::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case A_KEY:
		if (_allow[ATTACKING] && !_swingsword->IsOnScreen())
		{
			_allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState(_playerHandler));
			AttackWithSword();
		}
		break;

	case S_KEY:
		if (_allow[ATTACKING] && !_item->IsOnScreen())
		{
			_allow[ATTACKING] = false;
			ChangeState(new PlayerAttackingState(_playerHandler));
			AttackWithItem();
		}
		break;

	case D_KEY:
		if (_state == JUMPING || _state == FALLING)
		{
			_allow[ATTACKING] = false;
			AttackWithSwingSword();
		}
		break;

	case VK_SPACE:
		if (_allow[JUMPING])
		{
			_allow[JUMPING] = false;
			ChangeState(new PlayerJumpingState(_playerHandler));
		}
		break;
	}
}

// Xử lí các sự kiện thả phím của nhân vật
void Player::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	// Nếu thả phím DOWN thì quay về STANDING (dùng cho khi đang ATTACK)
	case VK_DOWN:
		if (_state == SITTING)
			_state = STANDING;
		break;
	}
}

// Đổi State
void Player::ChangeState(PlayerState * newState)
{
	_playerHandler->SetState(newState);
	_state = newState->GetName();
	ChangeAnimation(_state);
}

// Đổi Animation tương ứng theo State
void Player::ChangeAnimation(State state)
{
	_curAnimation = _animations[state];
	_width = _curAnimation->GetWidth();
	_height = _curAnimation->GetHeight();
}

void Player::ChangeSword(ObjectItemSword * sword)
{
	if (_sword) delete _sword;
	_sword = sword;
}


void Player::ChangeItem(ObjectItem * newItem)
{
	if (_item) delete _item;
	_item = newItem;
}

// Kiểm tra đã đến frame cuối của Animation hiện tại chưa
bool Player::IsLastFrame()
{
	return _curAnimation->IsLastFrame();
}

bool Player::IsReverse()
{
	return _isReverse;
}

void Player::Allow(State state, bool flag)
{
	_allow[state] = flag;
}

void Player::AttackWithSword()
{
	if (_sword != NULL)
	{
		_sword->Reverse(_isReverse);
		_sword->OnScreen(true);
	}
}

void Player::AttackWithSwingSword()
{
	if (_swingsword != NULL)
	{
		_swingsword->Reverse(_isReverse);
		_swingsword->OnScreen(true);
	}
}

void Player::AttackWithItem()
{
	if (_item != NULL)
	{
		_item->Reverse(_isReverse);
		_item->SetPosition(_posX, _posY);
		_item->OnScreen(true);
	}
}

bool Player::IsAllow(State state)
{
	return _allow[state];
}

ObjectItemSword* Player::GetSword()
{
	return _sword;
}

ObjectItemSwingSword * Player::GetSwingSword()
{
	return _swingsword;
}

ObjectItem* Player::GetItem()
{
	return _item;
}