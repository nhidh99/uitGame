#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <map>

// Các thông số và biến tổng dùng cho toàn bộ Game

#define WINDOW_CLASS_NAME "Ninja Gaiden"		// Class Windows
#define MAIN_WINDOW_TITLE "Ninja Gaiden"		// Tên cửa sổ
#define SCREEN_WIDTH 313						// Chiều rộng cửa sổ
#define SCREEN_HEIGHT 176						// Chiều dài cửa sổ
#define MAX_FRAME_RATE 80						// FPS
#define BACK_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
#define DEFAULT_TPS 150							// Thời gian tồn tại của mỗi Frame (cho Animation)
#define GRAVITY_SPEED 0.012f					// Tốc độ trọng lực
#define KEYBOARD_BUFFER_SIZE 1024
#define NUMBER_MAP_LEVEL 1
#define TILE_SIZE 16

// ===== Các thông số cho PLAYER ====
#define player Player::GetInstance()
#define PLAYER_RUNNING_SPEED 0.1f
#define PLAYER_JUMPING_SPEED 0.28f
#define PLAYER_FALLING_SPEED 0.25f
#define PLAYER_CLIMBING_SPEED 0.1f
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
#define ITEM_SHURIKEN_WIDTH 18
#define ITEM_SHURIKEN_HEIGHT 18
#define ITEM_SHURIKEN_SPEED 0.15f
#define ITEM_SWINGSWORD_WIDTH 18
#define ITEM_SWINGSWORD_HEIGHT 18

extern HINSTANCE hInstance;										// hInstance của windows hiện tại
extern HWND hWnd;												// hWnd hiện tại
extern LPD3DXSPRITE spriteHandler;								// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddev;								// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;							// BackBuffer
extern bool isGameRunning;										// Kiểm tra trạng thái game đang chạy
extern std::map<int, bool> keyCode;

// === ENUM dùng định dạng loại Object và State ====

extern enum Tag
{
	PLAYER,
	ITEM,
	GROUND,
	MAP1,
	ENEMY,
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

extern enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

extern enum EnemyType {
	SWORDMAN,
};