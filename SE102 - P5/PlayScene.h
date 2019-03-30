#pragma once
#include "Scene.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Player.h"
#include "ObjectGround.h"
#include "ObjectItemSword.h"
#include "ObjectItemShuriken.h"
#include "Camera.h"
#include <map>

class PlayScene : public Scene
{
private:
	Player* _player;
	Map* _map;
	Camera* _camera;
	int _leftCamera, _rightCamera;
	int _leftScreen, _rightScreen;
	std::vector<BoundingBox> grounds;

public:
	PlayScene();
	~PlayScene();
	void CameraUpdate();
	void Update(float dt);							// Update các thông số các đối tượng trong Scene
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};