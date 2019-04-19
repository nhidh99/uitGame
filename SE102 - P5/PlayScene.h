#pragma once
#include "Scene.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Player.h"
#include "ObjectItemSword.h"
#include "Camera.h"
#include "Map.h"
#include "EnemySwordMan.h"
#include <map>
#include <fstream>
#include <string>

class PlayScene : public Scene
{
private:
	Map* map;
	Camera* camera;
	std::vector<BoundingBox> grounds, visibleGrounds;
	std::vector<BoundingBox> walls, visibleWalls;
	std::vector<Enemy*> enemies;

public:
	PlayScene();
	~PlayScene();
	void CameraUpdate();
	void LoadResources(Type tag);
	void Update(float dt);							// Update các thông số các đối tượng trong Scene
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};