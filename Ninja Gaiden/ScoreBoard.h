#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "GameGlobal.h"
#include <unordered_map>
#include <string.h>
#include "SpriteFactory.h"
#include <vector>
#include <sstream>
#include "Player.h"

class ScoreBoard {
public:
	int score;
	int timer;
	int stage;
	int playerHealth;
	int bossHealth;
	int playerEnergy;
	bool isEndGame;
	Type playerWeapon;
	static ScoreBoard* _instance;

	ScoreBoard();


	void Render();
	void RenderScore();
	void RenderStage();
	void RenderTimer();
	void RenderEnergy();
	void RenderHealth(float x, float y);
	void RenderPlayerWeapon();
	void RenderPlayerHealth();
	void RenderEnemyHealth();
	void RenderString(std::string str, int x, int y);

	void Update(float dt);
	static ScoreBoard* GetInstance();
};