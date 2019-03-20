#pragma once
#include "GameGlobal.h"
#include "SceneManager.h"
#include "PlayScene.h"

class Game
{
public:
	Game(HWND hWnd);				// Constructor Game từ Windows đã tạo
	void Init(HWND hWnd);			// Khởi tạo các thông số cho Game
	void Run();						// Khởi chạy game, đồng thời chứa vòng lặp game
	void Update(float dt);			// Update game sau khoảng thời gian delta-time
	void Render();					// Render các Object có trong Game
};