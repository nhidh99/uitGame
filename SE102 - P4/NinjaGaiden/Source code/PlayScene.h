#pragma once
#include "Scene.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Player.h"
#include "ObjectItemSword.h"
#include "ObjectItemShuriken.h"
#include <map>

class PlayScene : public Scene
{
private:
	Player* _player;
	ObjectItem* _item;
	std::map<int, bool> _keyCode;

public:
	PlayScene();
	~PlayScene();
	void Update(float dt);							// Update các thông số các đối tượng trong Scene
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int keyCode);					// Xử lí Scene khi nhấn phím
	void OnKeyUp(int keyCode);						// Xử lí Scene khi thả phím
};