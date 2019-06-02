﻿#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>
#include "Grid.h"
#include "WeaponFactory.h"
#include "BulletFactory.h"
#include "ScoreBoard.h"

class PlayScene : public Scene
{
private:
	Map* map;
	Grid* grid;
	std::unordered_set<Object*> visibleObjects;
public:
	PlayScene();
	~PlayScene();

	void Update(float dt);
	void UpdateScene();						// Update các thông số các đối tượng trong Scene
	void UpdateVisibleObjects();
	void UpdateObjects(float dt);
	void UpdatePlayer(float dt);

	void RestartScene();
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};