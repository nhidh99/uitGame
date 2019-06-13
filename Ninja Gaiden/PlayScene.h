#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>
#include "Grid.h"
#include "WeaponFactory.h"
#include "BulletFactory.h"
#include "MapFactory.h"
#include "EndScene.h"
#include "SceneManager.h"

class PlayScene : public Scene
{
private:
	Player* p;
	Map* map;
	Grid* grid;
	int level;
	Rect endRect;
	float delayRestart;
	std::unordered_set<Object*> visibleObjects;

public:
	PlayScene(int level);
	~PlayScene();

	bool PlayerIsOnAirGround();
	void Update(float dt);
	void UpdateScoreboard(float dt);
	void UpdateScene();						// Update các thông số các đối tượng trong Scene
	void UpdateVisibleObjects();
	void UpdateObjects(float dt);
	void UpdatePlayer(float dt);
	void SetRestartScene();

	void RestartScene();
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};