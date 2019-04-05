#pragma once
#include "Scene.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Player.h"
#include "ObjectGround.h"
#include "ObjectItemSword.h"
#include "ObjectItemShuriken.h"
#include "Camera.h"
#include "SwordMan.h"
#include <map>
#include<fstream>
#include<string>
#include<iostream>


class PlayScene : public Scene
{
private:
	Map* _map;
	Camera* _camera;
	int _leftCamera, _rightCamera;
	int _leftScreen, _rightScreen;
	std::vector<BoundingBox> grounds;
	std::vector<Enemy*> _enemies;

	SwordMan* _sw;
public:
	PlayScene();
	~PlayScene();
	void CameraUpdate();
	void LoadResources(EnemyType type);
	void Update(float dt);							// Update các thông số các đối tượng trong Scene
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};