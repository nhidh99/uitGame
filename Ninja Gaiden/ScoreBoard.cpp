#include "ScoreBoard.h"

ScoreBoard* ScoreBoard::_instance = NULL;

ScoreBoard::ScoreBoard()
{
	score = 0;
	timer = GAME_TIMER;
	this->sprites = SpriteFactory::GetInstance();
	this->stage = 1;
	this->playerEnergy = 0;
	this->bossHealth = 16;
	this->playerHealth = 16;
	this->playerWeapon = NONE;
	this->isEndGame = false;
}

void ScoreBoard::Render()
{
	RenderScore();
	RenderTimer();
	RenderEnergy();
	RenderStage();
	RenderPlayerHealth();
	RenderEnemyHealth();
	RenderPlayerWeapon();
}

void ScoreBoard::RenderScore()
{
	std::string str;
	std::ostringstream convert;
	convert << score;
	str = convert.str();
	int n = std::strlen(str.c_str());
	char scoreArr[8];
	std::strcpy(scoreArr, str.c_str());

	RenderString("SCORE", 30, 15);
	sprites->GetSprite(FONT, 36)->ScaleRender(80, 15, SCALE_RATE, SCALE_RATE);

	for (int i = 0; i < 5 - n; i++)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(90 + i * 10, 15, SCALE_RATE, SCALE_RATE);
	}

	for (int i = 0; i < n; i++)
	{
		sprites->GetSprite(FONT, (int(scoreArr[i] - '0') + 26))->ScaleRender(90 + (6 - n + i) * 10, 15, SCALE_RATE, SCALE_RATE);
	}
}

void ScoreBoard::RenderStage()
{
	RenderString("STAGE", 155, 15);
	sprites->GetSprite(FONT, 36)->ScaleRender(205, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('3' - '0') + 26)->ScaleRender(215, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, 36)->ScaleRender(225, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('1' - '0') + 26)->ScaleRender(235, 15, SCALE_RATE, SCALE_RATE);
}

void ScoreBoard::RenderTimer()
{
	std::string str;
	std::ostringstream convert;
	convert << timer / 1000;
	str = convert.str();
	char timerArr[8];
	std::strcpy(timerArr, str.c_str());

	RenderString("TIMER", 30, 30);
	sprites->GetSprite(FONT, 36)->ScaleRender(80, 30, SCALE_RATE, SCALE_RATE);

	if (timer >= 100000)
	{
		for (int i = 0; i < 3; i++)
		{
			sprites->GetSprite(FONT, (int(timerArr[i] - '0') + 26))->ScaleRender(90 + 10 * i, 30, SCALE_RATE, SCALE_RATE);
		}
	}
	else if (timer < 10000)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(90, 30, SCALE_RATE, SCALE_RATE);
		sprites->GetSprite(FONT, 26)->ScaleRender(100, 30, SCALE_RATE, SCALE_RATE);
		sprites->GetSprite(FONT, (int(timerArr[0] - '0') + 26))->ScaleRender(110, 30, SCALE_RATE, SCALE_RATE);
	}
	else if (timer < 100000)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(90, 30, SCALE_RATE, SCALE_RATE);
		for (int i = 0; i < 2; i++)
		{
			sprites->GetSprite(FONT, (int(timerArr[i] - '0') + 26))->ScaleRender(100 + 10 * i, 30, SCALE_RATE, SCALE_RATE);
		}
	}
}

void ScoreBoard::RenderEnergy()
{
	std::string str;
	std::ostringstream convert;
	convert << playerEnergy;
	str = convert.str();
	int n = std::strlen(str.c_str());
	char energyArr[8];
	std::strcpy(energyArr, str.c_str());

	sprites->GetSprite(FONT, int('P' - 'A'))->ScaleRender(30, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, 36)->ScaleRender(40, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('0' - '0') + 26)->ScaleRender(50, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('2' - '0') + 26)->ScaleRender(60, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(ITEM, 1)->Render(75, 42);
	sprites->GetSprite(FONT, 36)->ScaleRender(90, 45, SCALE_RATE, SCALE_RATE);

	for (int i = 0; i < 2 - n; i++)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(90 + i * 10, 15, SCALE_RATE, SCALE_RATE);
	}

	for (int i = 0; i < n; ++i)
	{
		sprites->GetSprite(FONT, (int(energyArr[i] - '0') + 26))->ScaleRender(100 + (2 - n + i) * 10, 15, SCALE_RATE, SCALE_RATE);
	}
}

void ScoreBoard::RenderHealth(float x, float y)
{
	for (int i = 0; i < 16; ++i)
	{
		sprites->GetSprite(FONT, 37)->ScaleRender(x + i * 4, y, SCALE_RATE, SCALE_RATE);
	}

	if (this->playerHealth < 16)
	{
		int num = 16 - playerHealth;
		for (int j = 0; j < num; ++j)
		{
			sprites->GetSprite(FONT, 38)->ScaleRender(x + (playerHealth + j) * 4, y, SCALE_RATE, SCALE_RATE);
		}
	}
}

void ScoreBoard::RenderPlayerWeapon()
{
	switch (this->playerWeapon)
	{
	case BLUESHURIKEN:
		sprites->GetSprite(ITEM, 3)->ScaleRender(132, 40, 1.25, 1.25);
		break;
	default:
		break;
	}
}

void ScoreBoard::RenderPlayerHealth()
{
	RenderString("NINJA", 155, 30);
	sprites->GetSprite(FONT, 36)->ScaleRender(205, 30, SCALE_RATE, SCALE_RATE);
	RenderHealth(215, 30);
}

void ScoreBoard::RenderEnemyHealth()
{
	RenderString("ENEMY", 155, 45);
	sprites->GetSprite(FONT, 36)->ScaleRender(205, 45, SCALE_RATE, SCALE_RATE);

	for (int i = 0; i < 16; ++i)
	{
		sprites->GetSprite(FONT, 37)->ScaleRender(215 + i * 4, 45, SCALE_RATE, SCALE_RATE);
	}
}


void ScoreBoard::RenderString(std::string str, int x, int y)
{
	char cstr[8];
	std::strcpy(cstr, str.c_str());

	for (int i = 0; i < 5; ++i)
	{
		sprites->GetSprite(FONT, int(cstr[i] - 'A'))->ScaleRender(x + i * 10, y, SCALE_RATE, SCALE_RATE);
	}
}

void ScoreBoard::Update(float dt)
{
	if (isEndGame)
	{
		if (this->playerEnergy > 0)
		{
			this->score += 200;
			this->playerEnergy--;
		}

		if (this->timer > 0)
		{
			this->score += 200;
			this->timer -= 1000;
			Sound::getInstance()->play("sound9", false, 1);
		}

		if (this->timer == 0)
		{
			this->isEndGame = false;
		}
	}
	else
	{
		timer -= dt;
		this->playerHealth = player->health;
		this->playerEnergy = player->energy;
		this->playerWeapon = player->weaponType;
	}
}

ScoreBoard* ScoreBoard::GetInstance()
{
	if (_instance == NULL)
		_instance = new ScoreBoard();
	return _instance;
}