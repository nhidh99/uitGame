#pragma once
#include "GameGlobal.h"
#include "SpriteFactory.h"
#include "Scene.h"
#include "SceneManager.h"


class EndScene : public Scene
{
public:
	Sprite* background;

	EndScene();
	~EndScene();

	void Render();
};