#pragma once
#include "SpriteFactory.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "IntroScene.h"

class EndScene : public Scene
{
public:
	Sprite* background;

	EndScene();
	~EndScene();

	void Render();
	void OnKeyDown(int key);
};