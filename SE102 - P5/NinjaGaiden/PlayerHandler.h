#pragma once
class Player;
class PlayerState;

class PlayerHandler
{
private:
	Player* _player;
	PlayerState* _state;

public:
	~PlayerHandler()
	{
		if (_player) delete _player;
		if (_state) delete _state;
	}

	Player* GetPlayer() 
	{
		return _player;
	}

	PlayerState* GetState() 
	{
		return _state;
	}

	void SetPlayer(Player* player)
	{
		_player = player;
	}
	
	void SetState(PlayerState* state)
	{
		if (_state)
			delete _state;
		_state = state;
	}
};