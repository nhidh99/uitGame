#pragma once
class Player;
class PlayerState;

class PlayerHandler
{

public:
	Player* Player;
	PlayerState* State = nullptr;

	~PlayerHandler()
	{
		if (Player) delete Player;
		if (State) delete State;
	}
	
	void SetState(PlayerState* state)
	{
		delete State;
		State = state;
	}
};