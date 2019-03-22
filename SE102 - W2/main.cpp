/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Ball.h"

CGame *game;
CBall *ball;
CGameObject *paddle1, *paddle2;
int score1 = 0, score2 = 0;

// Xử lí các sự kiện cụ thể (lấy trạng thái phím đang được nhấn, nhấn phím và thả phím)
class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};
};

// Các trạng thái phím đang được nhấn
void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_W))
	{
		paddle1->AddPosY(-10.0f);
	}
	else if (game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_S))
	{
		paddle1->AddPosY(10.0f);
	}
}

class CSampleMouseHandler : public CMouseEventHandler
{
public:
	void OnMouseMove()
	{
		paddle2->AddPosY(game->GetMouseY());
	}
};

// Xử lí các thông điệp gửi đến Window
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

// Tải các Resource (gồm texture, sprite, animation) từ File dẫn cho trước
// Sau đó gắn vào các danh sách tương ứng, đồng thời thêm animation vào Ball
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	textures->Add(1, L"textures\\pong.png", NULL);
	textures->Add(2, L"textures\\score.png", NULL);
	auto texPong = textures->Get(1);
	auto texScore = textures->Get(2);

	// ========== BALL ===========
	sprites->Add(1, 10, 10, 40, 40, texPong);
	sprites->Add(2, 60, 10, 90, 40, texPong);
	sprites->Add(3, 110, 10, 140, 40, texPong);
	sprites->Add(4, 160, 10, 190, 40, texPong);
	sprites->Add(5, 210, 10, 240, 40, texPong);
	sprites->Add(6, 260, 10, 290, 40, texPong);
	sprites->Add(7, 310, 10, 340, 40, texPong);
	sprites->Add(8, 360, 10, 390, 40, texPong);
	sprites->Add(9, 410, 10, 440, 40, texPong);

	auto ani = new CAnimation(100);
	for (int i = 1; i <= 9; ++i)
		ani->Add(i);
	animations->Add(1, ani);

	ball = new CBall();
	ball->SetAnimation(animations->Get(1));
	ball->SetPosition((SCREEN_WIDTH >> 1), (SCREEN_HEIGHT >> 1));
	ball->SetSpeed((rand() & 2 ? -1 : 1) * 0.2f, (rand() & 2 ? -1 : 1)*(rand() % 5 + 1) / 10.0f);

	// ========== PADDLE 1 ============
	sprites->Add(10, 17, 44, 35, 119, texPong);
	ani = new CAnimation(100);
	ani->Add(10);
	animations->Add(2, ani);
	paddle1 = new CGameObject();
	paddle1->SetAnimation(animations->Get(2));
	paddle1->SetPosition((SCREEN_WIDTH >> 2), (SCREEN_HEIGHT >> 1));

	// ========== PADDLE 2 ============
	sprites->Add(11, 65, 44, 83, 119, texPong);
	ani = new CAnimation(100);
	ani->Add(11);
	animations->Add(3, ani);
	paddle2 = new CGameObject();
	paddle2->SetAnimation(animations->Get(3));
	paddle2->SetPosition(3 * (SCREEN_WIDTH >> 2), (SCREEN_HEIGHT >> 1));

	// ========== SCORE ===============
	sprites->Add(12, 2, 2, 20, 37, texScore);
	sprites->Add(13, 23, 2, 28, 37, texScore);
	sprites->Add(14, 30, 2, 47, 37, texScore);
	sprites->Add(15, 49, 2, 65, 37, texScore);
	sprites->Add(16, 68, 2, 84, 37, texScore);
	sprites->Add(17, 85, 2, 105, 37, texScore);
	sprites->Add(18, 106, 2, 122, 37, texScore);
	sprites->Add(19, 124, 2, 142, 37, texScore);
	sprites->Add(20, 144, 2, 162, 37, texScore);
	sprites->Add(21, 162, 2, 180, 37, texScore);
}

// Update các đối tượng (ở đây là Ball) sau một khoảng thời gian delta
void Update(DWORD dt)
{
	paddle1->Update(dt);
	paddle2->Update(dt);
	ball->Update(dt);

	if (ball->Collision(paddle1) || ball->Collision(paddle2))
	{
		ball->SetVx(-ball->GetVx());
	}

	else if (ball->GetPosY() < ball->GetHeight() >> 1 || ball->GetPosY() > (SCREEN_HEIGHT - ball->GetHeight()))
	{
		ball->SetVy(-ball->GetVy());
	}
	
	else if (ball->GetPosX() < paddle1->GetPosX())
	{
		++score2;
		ball->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);
		srand(time(NULL));
		ball->SetSpeed((rand() & 1 ? -1 : 1) * 0.2f, (rand() & 2 ? -1 : 1)*(rand() % 5 + 1) / 10.0f);
	}
	
	else if (ball->GetPosX() > paddle2->GetPosX())
	{
		++score1;
		ball->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);
		srand(time(NULL));
		ball->SetSpeed((rand() & 1 ? -1 : 1) * 0.2f, (rand() & 2 ? -1 : 1)*(rand() % 5 + 1) / 10.0f);
	}
}

void ScoreRender()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(12 + score1 / 10)->Draw(SCREEN_WIDTH >> 3, SCREEN_HEIGHT >> 3);
	sprites->Get(12 + (score1 % 10))->Draw((SCREEN_WIDTH >> 3) + 20, SCREEN_HEIGHT >> 3);
	sprites->Get(12 + (score2 / 10))->Draw(7 * (SCREEN_WIDTH >> 3) - 20, SCREEN_HEIGHT >> 3);
	sprites->Get(12 + (score2 % 10))->Draw(7 * (SCREEN_WIDTH >> 3), SCREEN_HEIGHT >> 3);
}

// Render các thành phần của Game
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		ball->Render();
		paddle1->Render();
		paddle2->Render();
		ScoreRender();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

// Tạo cửa sổ cho game
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
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

// Khởi chạy game
int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		// Xử lí các thông điệp gửi đến
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Nếu là thông điệp thoát thì dừng game
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		game->PollKeyboard();
		game->PollMouse();

		// Vòng lặp game chính
		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();	// Xử lí sự kiện bàn phím
			game->ProcessMouse();
			Update(dt);					// Update các đối tượng
			Render();					// Render các đối tượng
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	auto keyHandler = new CSampleKeyHander();
	auto mouseHandler = new CSampleMouseHandler();

	game->InitDirectInput();
	game->InitKeyboard(keyHandler);
	game->InitMouse(mouseHandler);

	LoadResources();
	Run();

	return 0;
}