#include "Game.h"
#include "debug.h"

CGame * CGame::__instance = NULL;

// Khởi tạo các đối tượng của DirectX
void CGame::Init(HWND hWnd)
{
	// Khởi tạo Direct3D
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// Khởi tạo cửa sổ
	this->hWnd = hWnd;

	// Khởi tạo các biến cho cửa sổ
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// Tạo device từ Direct3D phục vụ cho việc vẽ hình từ card đồ họa
	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	// Debug: kiểm tra khởi tạo device
	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	// Khởi tạo backbuffer
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Khởi tạo Sprite Handler
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

// Vẽ một Texture lên màn hình tại tọa độ (x,y) trong một khung hình chữ nhật có tọa độ trong Texture đó
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom)
{
	D3DXVECTOR3 p(x, y, 0);
	D3DXVECTOR3 c((right - left) >> 1, (bottom - top) >> 1, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, &c, &p, D3DCOLOR_XRGB(255, 255, 255));
}

// Kiểm tra có phím nào trên bàn phím nhấn xuống không
int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::InitDirectInput()
{
	DirectInput8Create
	(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL
	);
	
	di->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	di->CreateDevice(GUID_SysMouse, &dimouse, NULL);
}

// Khởi tạo bàn phím
void CGame::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	dikeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	dikeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	dikeyboard->Acquire();
	this->keyHandler = handler;
}

// Khởi tạo chuột
void CGame::InitMouse(CMouseEventHandler* handler)
{
	dimouse->SetDataFormat(&c_dfDIMouse);
	dimouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	dimouse->Acquire();
	this->mouseHandler = handler;
}

void CGame::PollKeyboard()
{
	dikeyboard->GetDeviceState(sizeof(keyStates), keyStates);
}

void CGame::PollMouse()
{
	dimouse->GetDeviceState(sizeof(mouseState), &mouseState);
}


// Xử lí sự kiện bàn phím
void CGame::ProcessKeyboard()
{
	keyHandler->KeyState((BYTE *)&keyStates);
	// Kiểm tra các sự kiện của keyboard
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	dikeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	// Scan các sự kiện, xem có phím nào được nhấn hay thả hay không
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

void CGame::ProcessMouse()
{
	mouseHandler->OnMouseMove();
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}


CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}