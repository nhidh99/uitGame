#pragma once
#include <d3dx9.h>
#include <d3d9.h>

// Các thông số và biến tổng dùng cho toàn bộ Game

#define WINDOW_CLASS_NAME "Deadline"			// Class Windows
#define MAIN_WINDOW_TITLE "Deadline"			// Tên cửa sổ
#define SCREEN_WIDTH 600						// Chiều rộng cửa sổ
#define SCREEN_HEIGHT 400						// Chiều dài cửa sổ
#define MAX_FRAME_RATE 60						// FPS
#define BACK_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
#define TIME_PER_FRAME 150						// Thời gian tồn tại của mỗi Frame (cho Animation)
#define GRAVITY_SPEED 0.3f						// Tốc độ trọng lực

// ===== Các thông số cho PLAYER ====
#define PLAYER_RUNNING_SPEED 0.15f
#define PLAYER_JUMPING_SPEED 0.015f
#define PLAYER_CLIMBING_SPEED 0.15f
#define PLAYER_WIDTH 24
#define PLAYER_STANDING_HEIGHT 33
#define PLAYER_SITTING_HEIGHT 24
#define PLAYER_ATTACK_SPRITE_WIDTH 34
#define PLAYER_ATTACKING_FORWARD 15
#define PLAYER_SITTING_BACKWARD 7
#define PLAYER_THROW_SPRITE_WIDTH 27
#define PLAYER_THROWING_FORWARD 5

// ===== Các thông số cho ITEM SWORD ====
#define ITEM_SWORD_WIDTH 16
#define ITEM_SWORD_HEIGHT 12

// ===== Các thông số cho ITEM SHURIKEN ====
#define ITEM_SHURIKEN_WIDTH 8
#define ITEM_SHURIKEN_HEIGHT 8
#define ITEM_SHURIKEN_SPEED 0.3f
#define ITEM_SWINGSWORD_WIDTH 18
#define ITEM_SWINGSWORD_HEIGHT 18

// === Các phím dùng xét Keyboard ===
#define A_KEY 0x41
#define D_KEY 0x44
#define S_KEY 0x53

extern HINSTANCE hInstance;						// hInstance của windows hiện tại
extern HWND hWnd;								// hWnd hiện tại
extern LPD3DXSPRITE spriteHandler;				// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddev;				// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;			// BackBuffer
extern bool isGameRunning;						// Kiểm tra trạng thái game đang chạy

// === ENUM dùng định dạng loại Object và State ====

extern enum Tag
{
	PLAYER,
	ITEM
};

extern enum Type
{
	SWORD,
	SHURIKEN,
	SWINGSWORD
};

extern enum State
{
	MOVING,
	STANDING,
	RUNNING,
	JUMPING,
	FALLING,
	SITTING,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	CLIMBING,
	DEAD,
	INJURED
};