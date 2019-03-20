#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"

#define WINDOW_CLASS_NAME "SampleWindow"
#define MAIN_WINDOW_TITLE "01 - Skeleton"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 30
#define RECT_WIDTH 20
#define RECT_HEIGHT 20

CGame *game;
LPDIRECT3DSURFACE9 surface = NULL;
RECT rect;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Update(DWORD dt)
{
	if (rect.top <= 0)
	{
		rect.top = 0;
		rect.bottom = RECT_HEIGHT;
		rect.left += 5*2;
		rect.right = rect.left + RECT_WIDTH;
	}
	if (rect.right >= SCREEN_WIDTH)
	{
		rect.right = SCREEN_WIDTH;
		rect.left = rect.right - RECT_WIDTH;
		rect.top += 5*2;
		rect.bottom = rect.top + RECT_HEIGHT;
	}
	if (rect.bottom >= SCREEN_HEIGHT)
	{
		rect.bottom = SCREEN_HEIGHT;
		rect.top = rect.bottom - RECT_HEIGHT;
		rect.left -= 5*2;
		rect.right = rect.left + RECT_WIDTH;
	}
	if (rect.left <= 0)
	{
		rect.left = 0;
		rect.right = RECT_WIDTH; 
		rect.top -= 5*2;
		rect.bottom = rect.top + RECT_HEIGHT;
	}


	/*if (rect.right > SCREEN_WIDTH)
	{
		rect.left = 0;
		rect.right = rect.left + RECT_WIDTH;
	}

	rect.left += 0.2f*dt*2;
	rect.right = rect.left + RECT_WIDTH;
	rect.top = (SCREEN_HEIGHT >> 1) + dt*sin(rect.left);
	rect.bottom = rect.top + RECT_HEIGHT;*/
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backBuffer = game->GetBackBuffer();
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);
		d3ddv->ColorFill(surface, NULL, D3DCOLOR_XRGB(0, 255, 255));
		d3ddv->StretchRect(surface, NULL, backBuffer, &rect, D3DTEXF_NONE);
		d3ddv->EndScene();
	}
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString("[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
	return 1;
}

void Init()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	d3ddv->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	rect.top = SCREEN_HEIGHT >> 1;
	rect.left = 0;
	rect.right = RECT_WIDTH;
	rect.bottom = rect.top + RECT_HEIGHT;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH + 16, SCREEN_HEIGHT + 40);
	game = CGame::GetInstance();
	game->Init(hWnd);

	Init();
	Run();
	return 0;
}