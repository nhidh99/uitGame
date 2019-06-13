#include "ScoreBoard.h"

ScoreBoard* ScoreBoard::_instance = NULL;

ScoreBoard::ScoreBoard()
{
	score = 0;
	timer = GAME_TIMER;
	this->sprites = SpriteFactory::GetInstance();
	this->stage = gameLevel;
	this->playerEnergy = 0;
	this->bossHealth = ENEMY_BOSS_HEALTH;
	this->playerHealth = PLAYER_HEALTH;
	this->playerWeapon = BLUESHURIKEN;
}

void ScoreBoard::Render()
{
	RenderScore();
	RenderTimer();
	RenderEnergy();
	RenderStage();
	RenderPlayerHealth();
	RenderPlayerWeapon();
	RenderEnemyHealth();
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

	RenderString("SCORE", 10, 15);
	sprites->GetSprite(FONT, 36)->ScaleRender(60, 15, SCALE_RATE, SCALE_RATE);

	for (int i = 0; i < 6 - n; i++)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(70 + i * 10, 15, SCALE_RATE, SCALE_RATE);
	}

	for (int i = 0; i < n; i++)
	{
		sprites->GetSprite(FONT, (int(scoreArr[i] - '0') + 26))->ScaleRender(70 + (6 - n + i) * 10, 15, SCALE_RATE, SCALE_RATE);
	}
}

void ScoreBoard::RenderStage()
{
	RenderString("STAGE", 135, 15);
	sprites->GetSprite(FONT, 36)->ScaleRender(185, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, 29)->ScaleRender(195, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, 36)->ScaleRender(205, 15, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, stage + 26)->ScaleRender(215, 15, SCALE_RATE, SCALE_RATE);
}

void ScoreBoard::RenderTimer()
{
	std::string str;
	std::ostringstream convert;
	convert << timer / 1000;
	str = convert.str();
	char timerArr[8];
	std::strcpy(timerArr, str.c_str());

	RenderString("TIMER", 10, 30);
	sprites->GetSprite(FONT, 36)->ScaleRender(60, 30, SCALE_RATE, SCALE_RATE);

	if (timer >= 100000)
	{
		for (int i = 0; i < 3; i++)
		{
			sprites->GetSprite(FONT, (int(timerArr[i] - '0') + 26))->ScaleRender(70 + 10 * i, 30, SCALE_RATE, SCALE_RATE);
		}
	}
	else if (timer < 10000)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(70, 30, SCALE_RATE, SCALE_RATE);
		sprites->GetSprite(FONT, 26)->ScaleRender(80, 30, SCALE_RATE, SCALE_RATE);
		sprites->GetSprite(FONT, (int(timerArr[0] - '0') + 26))->ScaleRender(90, 30, SCALE_RATE, SCALE_RATE);
	}
	else if (timer < 100000)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(70, 30, SCALE_RATE, SCALE_RATE);
		for (int i = 0; i < 2; i++)
		{
			sprites->GetSprite(FONT, (int(timerArr[i] - '0') + 26))->ScaleRender(80 + 10 * i, 30, SCALE_RATE, SCALE_RATE);
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

	sprites->GetSprite(FONT, int('P' - 'A'))->ScaleRender(10, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, 36)->ScaleRender(20, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('0' - '0') + 26)->ScaleRender(30, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(FONT, int('2' - '0') + 26)->ScaleRender(40, 45, SCALE_RATE, SCALE_RATE);
	sprites->GetSprite(ITEM, 1)->Render(55, 42);
	sprites->GetSprite(FONT, 36)->ScaleRender(70, 45, SCALE_RATE, SCALE_RATE);

	for (int i = 0; i < 2 - n; i++)
	{
		sprites->GetSprite(FONT, 26)->ScaleRender(80 + i * 10, 45, SCALE_RATE, SCALE_RATE);
	}

	for (int i = 0; i < n; ++i)
	{
		sprites->GetSprite(FONT, (int(energyArr[i] - '0') + 26))->ScaleRender(80 + (2 - n + i) * 10, 45, SCALE_RATE, SCALE_RATE);
	}
}

void ScoreBoard::RenderHealth(float x, float y, int obj)
{
	for (int i = 0; i < 16; ++i)
	{
		sprites->GetSprite(FONT, 37)->ScaleRender(x + i * 3, y, SCALE_RATE, SCALE_RATE);
	}

	switch (obj)
	{
	case 1:
	{
		if (this->playerHealth < 16)
		{
			int num = 16 - playerHealth;
			for (int j = 0; j < num; ++j)
			{
				sprites->GetSprite(FONT, 38)->ScaleRender(x + (playerHealth + j) * 3, y, SCALE_RATE, SCALE_RATE);
			}
		}
		break;
	}
	case 2:
		if (this->bossHealth < 16)
		{
			int num = 16 - bossHealth;
			for (int j = 0; j < num; ++j)
			{
				sprites->GetSprite(FONT, 38)->ScaleRender(x + (bossHealth + j) * 3, y, SCALE_RATE, SCALE_RATE);
			}
		}
		break;
	}
}

void ScoreBoard::RenderPlayerWeapon()
{
	sprites->GetSprite(FONT, 39)->ScaleRender(121, 25, 0.8, 0.8);
	sprites->GetSprite(FONT, 40)->ScaleRender(101, 25, 0.8, 0.8);
	sprites->GetSprite(FONT, 41)->ScaleRender(101, 45, 0.8, 0.8);
	sprites->GetSprite(FONT, 42)->ScaleRender(121, 45, 0.8, 0.8);

	switch (this->playerWeapon)
	{
	case BLUESHURIKEN:
		sprites->GetSprite(ITEM, 3)->ScaleRender(113, 35, 1.25, 1.25);
		break;
	case FIREWHEEL:
		sprites->GetSprite(ITEM, 5)->ScaleRender(113, 35, 1.25, 1.25);
		break;
	case REDSHURIKEN:
		sprites->GetSprite(ITEM, 8)->ScaleRender(113, 35, 1.25, 1.25);
		break;
	default:
		break;
	}
}

void ScoreBoard::RenderPlayerHealth()
{
	RenderString("NINJA", 135, 30);
	RenderHealth(190, 30, 1);
	sprites->GetSprite(FONT, 36)->ScaleRender(185, 30, SCALE_RATE, SCALE_RATE);
}

void ScoreBoard::RenderEnemyHealth()
{
	RenderString("ENEMY", 135, 45);
	RenderHealth(190, 45, 2);
	sprites->GetSprite(FONT, 36)->ScaleRender(185, 45, SCALE_RATE, SCALE_RATE);
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
			this->score += 100;
			this->timer -= 500;
		}
		Sound::getInstance()->play("glasshour");

		if (timer < 0)
		{
			timer = 0;
		}
	}
	else
	{
		timer -= dt;
	}
}

ScoreBoard* ScoreBoard::GetInstance()
{
	if (_instance == NULL)
		_instance = new ScoreBoard();
	return _instance;
}