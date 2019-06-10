#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "SpriteFactory.h"
#include <sstream>
#include "Sound.h"

class ScoreBoard {
public:
	int score;
	int timer;
	int stage;
	int playerHealth;
	int bossHealth;
	int playerEnergy;
	Type playerWeapon;
	SpriteFactory* sprites;

	ScoreBoard();
	void Render();
	void Update(float dt);
	static ScoreBoard* GetInstance();

private:
	static ScoreBoard* _instance;
	void RenderScore();
	void RenderStage();
	void RenderTimer();
	void RenderEnergy();
	void RenderHealth(float x, float y, int type);
	void RenderPlayerWeapon();
	void RenderPlayerHealth();
	void RenderEnemyHealth();
	void RenderString(std::string str, int x, int y);
};