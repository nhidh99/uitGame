#pragma once
#include "GameGlobal.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include <WinUser.h>

class Game
{
private:
	LPDIRECTINPUT8 di;										// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device
	BYTE  keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	
public:
	Scene* CurScene;
	Game(HWND hWnd);				// Constructor Game từ Windows đã tạo
	void Init(HWND hWnd);			// Khởi tạo các thông số cho Game
	void Run();						// Khởi chạy game, đồng thời chứa vòng lặp game
	void Update(float dt);			// Update game sau khoảng thời gian delta-time
	void Render();					// Render các Object có trong Game
	void ProcessKeyboard();
};