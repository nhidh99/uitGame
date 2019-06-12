#pragma once
#include "Scene.h"
#include "GameGlobal.h"
#include "Sprite.h"
#include "SpriteFactory.h"
#include "SceneManager.h"
#include "PlayScene.h"

class IntroScene : public Scene
{
public:
	Sprite* ninjaSprite;
	Sprite* game_nameSprite;
	Sprite* game_infoSprite;
	Sprite* stageSprite;
	float vx;
	float vy;

	IntroScene();
	~IntroScene();

	void Render();
	void Update(float dt);
	void OnKeyDown(int key);
};