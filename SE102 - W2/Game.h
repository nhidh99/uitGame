#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define WINDOW_CLASS_NAME L"Pong Game"
#define MAIN_WINDOW_TITLE L"Pong Game"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define MAX_FRAME_RATE 90

/*
Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef CKeyEventHandler * LPKEYEVENTHANDLER;


class CMouseEventHandler
{
protected:
	DIMOUSESTATE mouseState;

public:
	LONG GetPosX() { return mouseState.lX; };
	LONG GetPosY() { return mouseState.lY; };
	virtual void OnMouseMove() = 0;
};

class CGame
{
	static CGame * __instance;
	HWND hWnd;												// Window handle

	LPDIRECT3D9 d3d = NULL;									// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;							// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;						// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8 di;										// The DirectInput object         
	LPDIRECTINPUTDEVICE8 dikeyboard;						// The keyboard device 
	LPDIRECTINPUTDEVICE8 dimouse;

	BYTE  keyStates[256];									// DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	DIMOUSESTATE mouseState;

	LPKEYEVENTHANDLER keyHandler;
	CMouseEventHandler* mouseHandler;

public:
	void InitDirectInput();
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void InitMouse(CMouseEventHandler* handler);
	void PollKeyboard();
	void PollMouse();
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void ProcessMouse();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	int GetMouseY() { return this->mouseState.lY; }

	static CGame * GetInstance();

	~CGame();
};


